#include "iMapMsgService.h"

map<int, ACE_SOCK_Stream> iMapMsgService::m_nProcMapSocket;
ACE_Thread_Mutex iMapMsgService::m_mapMutex;

iMapMsgService::iMapMsgService()
{

}

iMapMsgService::~iMapMsgService()
{

}

int iMapMsgService::open(void *p)
{
    
    if (ACE_Svc_Handler::open(p) == -1)
    {
        return -1;
    }
    
    ACE_TCHAR peer_name[512];
    ACE_INET_Addr peer_addr;
    if (this->peer().get_remote_addr(peer_addr) == 0
        && peer_addr.addr_to_string(peer_name, 512) == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::open>>connection success.peer_name:%s\n", peer_name));
    }

    return 0;
}

int iMapMsgService::handle_input(ACE_HANDLE fd)
{
    //定义一个消息
    iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

    //从内核缓存区读取消息头
    char buf[2048] = { 0 };
    int recv_cnt = 0;
    while (true)
    {
        recv_cnt = peer().recv_n(buf, pCmdMsg->GetMsgHeaderLength());
        if (recv_cnt > 0)
        {
            if (pCmdMsg->GetMsgHeaderLength() == recv_cnt)
            {
                break;
            }
            else if ((recv_cnt < pCmdMsg->GetMsgHeaderLength()))
            {
                continue;
            }
        }

        if (recv_cnt == 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, HeaderLength:%d, errno:%d\n", recv_cnt, pCmdMsg->GetMsgHeaderLength(), errno));
            return -1;
        }

        if (recv_cnt < 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, HeaderLength:%d, errno:%d\n", recv_cnt, pCmdMsg->GetMsgHeaderLength(), errno));
            return 0;
        }
    }

    //序列化消息头
    string strMsgHeader(buf, recv_cnt);
    pCmdMsg->deserializeHeader(strMsgHeader);

    //从内核缓存区读取消息体
    ACE_OS::memset(buf, 0, 2048);
    recv_cnt = 0;
    while (true)
    {
        int recv_cnt = peer().recv_n(buf, pCmdMsg->GetMsgBodyLength());
        if (recv_cnt > 0)
        {
            if (pCmdMsg->GetMsgBodyLength() == recv_cnt)
            {
                break;
            }
            else if (recv_cnt < pCmdMsg->GetMsgBodyLength())
            {
                continue;
            }
        }

        if (recv_cnt == 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgService::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
            return -1;
        }

        if (recv_cnt < 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
            return 0;
        }
    }

    //序列化消息体
    string strMsgBody(buf, pCmdMsg->GetMsgBodyLength());
    pCmdMsg->deserializeBody(strMsgBody);
    
    int nLength = pCmdMsg->GetMsgLength();
    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    mb->copy((char*)pCmdMsg, nLength);

    return SendCmdMsgToQueue(pCmdMsg);
}

int iMapMsgService::handle_output(ACE_HANDLE fd)
{
    ACE_Guard<ACE_Thread_Mutex> guard(m_mapMutex);
    ACE_Message_Block* pMsgBlock = NULL;
    ACE_Time_Value nowait(ACE_OS::gettimeofday());
    while (this->getq(pMsgBlock, &nowait) != -1)
    {
        if (pMsgBlock->msg_type() == ACE_Message_Block::MB_STOP)
        {
            pMsgBlock->release();
            break;
        }

        iMapCmdMsg *pCmdMsg = (iMapCmdMsg*)pMsgBlock->base();
        int nLength = pMsgBlock->length();
        
        if (pCmdMsg->GetMrbCmdMsg() == CMD_MSG_SERVICE_REGISTER)
        {
            m_nProcMapSocket.insert(map<int, ACE_SOCK_Stream>::value_type(pCmdMsg->GetSendProc(), peer()));
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgService::handle_output>>m_nProcMapSocket.size:%d\n", m_nProcMapSocket.size()));
        }
        else
        {
            //转发到其他进程
            if (pCmdMsg->GetMsgType() == REQUEST_MSG_TYPE)
            {
                SendCmdMsgToProc(pCmdMsg, pCmdMsg->GetRecvProc());
            }
            else if (pCmdMsg->GetMsgType() == RESPONSE_MSG_TYPE)
            {
                SendCmdMsgToProc(pCmdMsg, pCmdMsg->GetSendProc());
            }
            pCmdMsg->display("display");
            
        }

        //释放block
        pMsgBlock->release();
        pMsgBlock = NULL;

    }

    return (this->msg_queue()->is_empty()) ? -1 : 0;
}

// 释放相应资源
int iMapMsgService::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
        return 0;
    return ACE_Svc_Handler::handle_close(handle, mask);
}

int iMapMsgService::SendCmdMsgToQueue(iMapCmdMsg *pCmdMsg)
{
    int nLength = pCmdMsg->GetMsgLength();
    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    mb->copy((char*)pCmdMsg, nLength);

    int IsQueueEmpty = this->msg_queue()->is_empty();
    ACE_Time_Value nowait(ACE_OS::gettimeofday());
    if (this->putq(mb, &nowait) == -1)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::SendCmdMsgToQueue>>enqueue failed"));
        mb->release();
        return 0;
    }

    if (IsQueueEmpty)
    {
        return this->reactor()->register_handler(this, ACE_Event_Handler::WRITE_MASK);
    }

    return 0;
}

int iMapMsgService::SendCmdMsgToProc(iMapCmdMsg *pCmdMsg, int nProcID)
{
    map<int, ACE_SOCK_Stream>::iterator iter = m_nProcMapSocket.find(nProcID);
    if (iter != m_nProcMapSocket.end())
    {
        //序列化消息体
        string strMsgBody = pCmdMsg->serializeBody();
        pCmdMsg->SetMsgBodyLength(strMsgBody.size());
        //序列化消息头
        string strMsgHeader = pCmdMsg->serializeHeader();

        string strMsg = strMsgHeader + strMsgBody;
        while (true)
        {
            int send_cnt = iter->second.send_n(strMsg.c_str(), strMsg.length());
            if (send_cnt > 0)
            {
                
                if (strMsg.length() == send_cnt)
                {
                    break;
                }
                else if (send_cnt < strMsg.length())
                {
                    continue;
                }
                {
                    break;
                }
            }

            if (send_cnt == 0)
            {
                ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>send_cnt:%d, errno:%d\n", send_cnt, errno));
                return -1;
            }

            if (send_cnt < 0)
            {
                ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", send_cnt, errno));
                return 0;
            }
        }

        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>nMsgType:%d, strMsg.size:%d, errno:%d\n", pCmdMsg->GetMsgType(), strMsg.size(), errno));
    }

    return 0;
}

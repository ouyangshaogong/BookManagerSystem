#include "iMapMsgHandle.h"

MyMsgQueue g_MsgQueue;


map<int, ACE_SOCK_Stream> iMapMsgHandle::m_nProcMapSocket;
ACE_Thread_Mutex iMapMsgHandle::m_mapMutex;

iMapMsgHandle::iMapMsgHandle()
    :m_mMsgMutex(), m_mMsgCond(m_mapMutex)
{
    
}

iMapMsgHandle::~iMapMsgHandle()
{

}

int iMapMsgHandle::open(void *p)
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

int iMapMsgHandle::handle_input(ACE_HANDLE fd)
{
    const int BUFFER_MAX_LENGTH = 2048;
    //从内核缓存区读取消息头
    char buf[BUFFER_MAX_LENGTH] = { 0 };
    int recv_cnt = peer().recv(buf, BUFFER_MAX_LENGTH);
    if (recv_cnt > 0)
    {
        if (!m_MsgQueue.parser(buf, recv_cnt))
        {
            cout << "parser msg failed!" << endl;
        }
        else
        {
            cout << "parser msg successful!" << endl;
            m_mMsgCond.signal();
        }
    }

    if (recv_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return -1;
    }

    if (recv_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return 0;
    }

    return 0;
}

/*int iMapMsgHandle::handle_output(ACE_HANDLE fd)
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

        MyProtoMsg* pMsg = (MyProtoMsg*)pMsgBlock->base();
        int nLength = pMsgBlock->length();
        
        if (pMsg->Header.nCmdMsg == CMD_MSG_SERVICE_REGISTER)
        {
            m_nProcMapSocket.insert(map<int, ACE_SOCK_Stream>::value_type(pMsg->Header.nSendProc, peer()));
            pMsg->Header.nMsgType = RESPONSE_MSG_TYPE;
            SendCmdMsgToProc(pMsg, pMsg->Header.nSendProc);
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgService::handle_output>>m_nProcMapSocket.size:%d\n", m_nProcMapSocket.size()));
        }
        else
        {
            //转发到其他进程
            if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
            {
                SendCmdMsgToProc(pMsg, pMsg->Header.nRecvProc);
            }
            else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
            {
                SendCmdMsgToProc(pMsg, pMsg->Header.nSendProc);
            }

            pMsg->Header.display();
            
        }

        //释放block
        pMsgBlock->release();
        pMsgBlock = NULL;

    }

    return (this->msg_queue()->is_empty()) ? -1 : 0;
}*/

void iMapMsgHandle::StartMsgLoop()
{
    while (true)
    {
        if(m_MsgQueue.empty())
        {
            m_mMsgCond.wait();
        }

        MyProtoMsg* pMsg = NULL;
        while(!m_MsgQueue.empty())
        {
            pMsg = m_MsgQueue.front();
            
            if (pMsg->Header.nCmdMsg == CMD_MSG_SERVICE_REGISTER)
            {
                m_nProcMapSocket.insert(map<int, ACE_SOCK_Stream>::value_type(pMsg->Header.nSendProc, peer()));
                pMsg->Header.nMsgType = RESPONSE_MSG_TYPE;
                SendCmdMsgToProc(pMsg, pMsg->Header.nSendProc);
                ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgService::handle_output>>m_nProcMapSocket.size:%d\n", m_nProcMapSocket.size()));
            }
            else
            {
                //转发到其他进程
                if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
                {
                    SendCmdMsgToProc(pMsg, pMsg->Header.nRecvProc);
                }
                else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
                {
                    SendCmdMsgToProc(pMsg, pMsg->Header.nSendProc);
                }

                pMsg->Header.display();
                
            }

            m_MsgQueue.pop();
        }
    }
}


// 释放相应资源
int iMapMsgHandle::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
        return 0;
    return ACE_Svc_Handler::handle_close(handle, mask);
}

/*int iMapMsgHandle::SendCmdMsgToQueue(MyProtoMsg *pMsg)
{
    int nLength = pMsg->Header.nMsgLength;
    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    mb->copy((char*)pMsg, nLength);

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
}*/

int iMapMsgHandle::SendCmdMsgToProc(MyProtoMsg *pMsg, int nProcID)
{
    uint32_t length = 0;
    uint8_t* pData = NULL;

    map<int, ACE_SOCK_Stream>::iterator iter = m_nProcMapSocket.find(nProcID);
    if (iter != m_nProcMapSocket.end())
    {
        pData = m_protoEncode.encode(pMsg, length);
    }
    else
    {
        if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
        {
            iter = m_nProcMapSocket.find(pMsg->Header.nSendProc);
            if (iter != m_nProcMapSocket.end())
            {
                pMsg->Header.nMsgRet = -1;
                pMsg->Header.nMsgType = RESPONSE_MSG_TYPE;
                pData = m_protoEncode.encode(pMsg, length);
            }
            else
            {
                ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>service is not register!"));
                return 0;
            }
        }
        else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>service is not register!"));
            return 0;
        }
    }

    int send_cnt = 0;

    send_cnt = iter->second.send(pData, length);
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

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>send_cnt:%d, errno:%d\n", send_cnt, errno));

    return 0;
}

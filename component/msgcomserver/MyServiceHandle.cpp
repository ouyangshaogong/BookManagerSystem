#include "MyServiceHandle.h"

MyMsgServer *MyServiceHandle::m_pMsgServer = NULL;

MyServiceHandle::MyServiceHandle()
{
    m_pMsgServer = MyMsgServer::Instance();
}

MyServiceHandle::~MyServiceHandle()
{

}

int MyServiceHandle::open(void *p)
{
    if (ACE_Svc_Handler::open(p) == -1)
    {
        return -1;
    }
    
    if (this->peer().get_remote_addr(m_peerAddr) == 0
        && m_peerAddr.addr_to_string(m_peerName, 512) == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::open>>connection success.peer_name:%s\n", m_peerName));
    }

    m_pMsgServer->GetSockPeer(m_peerName, &this->peer());
    return 0;
}

int MyServiceHandle::handle_input(ACE_HANDLE fd)
{
    const int BUFFER_MAX_LENGTH = 2048;
    //从内核缓存区读取消息头
    char buf[BUFFER_MAX_LENGTH] = { 0 };
    int recv_cnt = peer().recv(buf, BUFFER_MAX_LENGTH);
    if (recv_cnt > 0)
    {
        if (!m_pMsgServer->parser(buf, recv_cnt))
        {
            cout << "parser msg failed!" << endl;
        }
        else
        {
            cout << "parser msg successful!" << endl;
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

int MyServiceHandle::handle_output(ACE_HANDLE fd)
{
    return 0;
}

// 释放相应资源
int MyServiceHandle::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
        return 0;
    if (this->peer().get_remote_addr(m_peerAddr) == 0
        && m_peerAddr.addr_to_string(m_peerName, 512) == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::open>>connection success.peer_name:%s\n", m_peerName));
    }

    m_pMsgServer->DeleteSockPeer(m_peerName);
    return ACE_Svc_Handler::handle_close(handle, mask);
}

//int MyServiceHandle::SendCmdMsgToQueue(MyProtoMsg *pMsg)
//{
//    int nLength = pMsg->Header.nMsgLength;
//    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
//    mb->copy((char*)pMsg, nLength);
//
//    int IsQueueEmpty = this->msg_queue()->is_empty();
//    ACE_Time_Value nowait(ACE_OS::gettimeofday());
//    if (this->putq(mb, &nowait) == -1)
//    {
//        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::SendCmdMsgToQueue>>enqueue failed"));
//        mb->release();
//        return 0;
//    }
//
//    if (IsQueueEmpty)
//    {
//        return this->reactor()->register_handler(this, ACE_Event_Handler::WRITE_MASK);
//    }
//
//    return 0;
//}

//int MyServiceHandle::SendCmdMsgToProc(MyProtoMsg *pMsg, int nProcID)
//{
//    uint32_t length = 0;
//    uint8_t* pData = NULL;
//
//    /*map<int, ACE_SOCK_Stream>::iterator iter = m_nProcMapSocket.find(nProcID);
//    if (iter != m_nProcMapSocket.end())
//    {
//        pData = m_pMsgQueue->encode(pMsg, length);
//    }
//    else
//    {
//        if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
//        {
//            iter = m_nProcMapSocket.find(pMsg->Header.nSendProc);
//            if (iter != m_nProcMapSocket.end())
//            {
//                pMsg->Header.nMsgRet = -1;
//                pMsg->Header.nMsgType = RESPONSE_MSG_TYPE;
//                pData = m_pMsgQueue->encode(pMsg, length);
//            }
//            else
//            {
//                ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>service is not register!"));
//                return 0;
//            }
//        }
//        else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
//        {
//            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>service is not register!"));
//            return 0;
//        }
//    }
//
//    int send_cnt = 0;
//
//    send_cnt = iter->second.send(pData, length);
//    if (send_cnt == 0)
//    {
//        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>send_cnt:%d, errno:%d\n", send_cnt, errno));
//        return -1;
//    }
//
//    if (send_cnt < 0)
//    {
//        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", send_cnt, errno));
//        return 0;
//    }
//
//    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>send_cnt:%d, errno:%d\n", send_cnt, errno));
//*/
//    return 0;
//}

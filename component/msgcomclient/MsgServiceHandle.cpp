#include "MsgServiceHandle.h"

MyMsgQueue *MsgServiceHandle::m_pMsgQueue = NULL;


MsgServiceHandle::MsgServiceHandle()
{
    MyMsgServer = MyMsgServer::Instance();
}

MsgServiceHandle::~MsgServiceHandle()
{

}

int MsgServiceHandle::open(void *p)
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

    MyMsgServer->GetSockPeer(m_peerName, &peer());

    return 0;
}

int MsgServiceHandle::handle_input(ACE_HANDLE fd)
{
    const int BUFFER_MAX_LENGTH = 2048;
    //从内核缓存区读取消息头
    char buf[BUFFER_MAX_LENGTH] = { 0 };
    int recv_cnt = peer().recv(buf, BUFFER_MAX_LENGTH);
    if (recv_cnt > 0)
    {
        if (!MyMsgServer->parser(buf, recv_cnt))
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

int MsgServiceHandle::handle_output(ACE_HANDLE fd)
{
    return 0;
}

// 释放相应资源
int MsgServiceHandle::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
    {
        return 0;
    }
    
    if (this->peer().get_remote_addr(m_peerAddr) == 0
        && m_peerAddr.addr_to_string(m_peerName, 512) == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::open>>connection success.peer_name:%s\n", m_peerName));
    }
    MyMsgServer->DeleteSockPeer(m_peerName);

    return ACE_Svc_Handler::handle_close(handle, mask);
}

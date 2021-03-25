#include "iMapMsgHandle.h"

iMapMsgHandle *iMapMsgHandle::m_instance = NULL;
ACE_Thread_Mutex iMapMsgHandle::m_mutex;

iMapMsgHandle::iMapMsgHandle()
    :m_MsgCond(m_MsgMutex)
{

}

iMapMsgHandle::~iMapMsgHandle()
{

}

iMapMsgHandle* iMapMsgHandle::Instance()
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new iMapMsgHandle;
        }
    }

    return m_instance;
}

int iMapMsgHandle::open(void *p)
{
    //注册输入事件为读数据
    ACE_Reactor::instance()->register_handler(m_instance, ACE_Event_Handler::READ_MASK);
    ACE_Reactor::instance()->register_handler(m_instance, ACE_Event_Handler::WRITE_MASK);

    return 0;
}

ACE_SOCK_Stream& iMapMsgHandle::Peer()
{
    return m_socketPeer;
}

ACE_HANDLE iMapMsgHandle::get_handle() const
{
    return this->m_socketPeer.get_handle();
}

int iMapMsgHandle::handle_input(ACE_HANDLE fd)
{
    char buf[2048] = { 0 };
    int recv_cnt = this->m_socketPeer.recv_n(buf, sizeof(buf) - 1);
    if (recv_cnt > 0)
    {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("%d, %s"), recv_cnt, buf));
        return 0;
    }

    iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

    string strCmsMsg = buf;
    pCmdMsg->deserialize(strCmsMsg);

    RecvExternalCmdMsg(pCmdMsg);

    return 0;
}

int iMapMsgHandle::handle_timeout(const ACE_Time_Value &current_time, const void *act)
{
    
}

int iMapMsgHandle::handle_output(ACE_HANDLE)
{
    bool bIsQuitLoop = true;
    while (true)
    {
        m_MsgCond.wait(m_MsgMutex);
        while (m_iMapCmdMsg.empty())
        {
            iMapCmdMsg *pCmdMsg = m_iMapCmdMsg.back();
            m_iMapCmdMsg.pop_back();
            if (pCmdMsg->GetMsgType() == REQUEST_MSG_TYPE)
            {
                //发送消息到网络上
                SendExternalCmdMsg(pCmdMsg);
            }
            else if (pCmdMsg->GetMsgType() == RESPONSE_MSG_TYPE)
            {
                //发送消息到应用程序内部
                SendInternalCmdMsg(pCmdMsg);
            }
            else if (pCmdMsg->GetMsgType() == END_MSG_TYPE)
            {
                bIsQuitLoop = true;
                break;
            }
        }

        if (bIsQuitLoop)
        {
            ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::handle_output>>Quit Message Loop!"));
            break;
        }
    }
}


void iMapMsgHandle::StartMsgLoop()
{
    while (1)
    {
        ACE_Reactor::instance()->handle_events();
    }
        
}

void iMapMsgHandle::SendExternalCmdMsg(iMapCmdMsg *pCmdMsg)
{

}

void iMapMsgHandle::SendInternalCmdMsg(iMapCmdMsg *pCmdMsg)
{

}

void iMapMsgHandle::RecvExternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    m_iMapCmdMsg.push_front(pCmdMsg);
    m_MsgCond.signal();
}

void iMapMsgHandle::RecvInternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    m_iMapCmdMsg.push_front(pCmdMsg);
    m_MsgCond.signal();
}
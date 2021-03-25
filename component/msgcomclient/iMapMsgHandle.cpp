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
    activate();

    return 0;
}

int iMapMsgHandle::close(u_long)
{
    ACE_DEBUG((LM_DEBUG, "(%t) Active Object being closed down \n"));
    return 0;
}

int iMapMsgHandle::svc(void)
{
    ACE_DEBUG((LM_DEBUG, "(%t) This is being done in a separate thread \n"));
    while (true)
    {
        ACE_Message_Block * mb = NULL;
        m_mqCmdMsg.dequeue(mb);
        if (NULL != mb)
        {
            iMapCmdMsg *pCmdMsg = (iMapCmdMsg*)mb->base();
            delete mb;
            mb = NULL;

            ACE_DEBUG((LM_DEBUG, "(%t) This is being done in a separate thread \n"));

        }
    }
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

    string strMsg = buf;
    pCmdMsg->deserialize(strMsg);
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
                int nlength = pCmdMsg->GetMsgHeaderLength() + sizeof(pCmdMsg->GetBody().length());
                SendInternalCmdMsg(pCmdMsg, nlength);
            }
            else if (pCmdMsg->GetMsgType() == END_MSG_TYPE)
            {
                //结束消息循环
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
    string strMsg = pCmdMsg->serialize();
    int recv_cnt = this->m_socketPeer.send_n(strMsg.c_str(), strMsg.size());
}

void iMapMsgHandle::SendInternalCmdMsg(iMapCmdMsg *pCmdMsg, int nlength)
{

    ACE_Message_Block*  mb1 = new ACE_Message_Block(nlength, ACE_Message_Block::MB_DATA);

    mb1->copy((char*)pCmdMsg, sizeof(nlength));

    int result1 = m_mqCmdMsg.enqueue(mb1);
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::SendInternalCmdMsg\n"));
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
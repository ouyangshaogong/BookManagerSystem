#include "iMapMsgHandle.h"

#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

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
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::open>>register_handler:READ_MASK,WRITE_MASK\n"));

    
    ACE_INET_Addr addr(PORT_NO, HOSTNAME);
    ACE_Time_Value timeout(5, 0);
    if (m_connector.connect(m_socketPeer, addr, &timeout) != 0)
    {
        ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::open>>connecetd fail"));
        return false;
    }
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK);
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::WRITE_MASK);
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::open>>connecetd entablish!"));

    activate();

    return 0;
}

ACE_HANDLE iMapMsgHandle::get_handle(void) const
{
    return m_socketPeer.get_handle();
}

int iMapMsgHandle::close(u_long)
{
    ACE_DEBUG((LM_DEBUG, "(%t) Active Object being closed down \n"));
    return 0;
}

int iMapMsgHandle::svc(void)
{
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::svc>>begin\n"));
    while (true)
    {
        ACE_Message_Block * mb = NULL;
        m_mqCmdMsg.dequeue(mb);
        if (NULL != mb)
        {
            iMapCmdMsg *pCmdMsg = (iMapCmdMsg*)mb->base();
            delete mb;
            mb = NULL;

            ACE_DEBUG((LM_DEBUG, "(%t) iMapMsgHandle::svc>>cmdmsg is reach to server\n"));

        }
    }
    return 0;
}

int iMapMsgHandle::handle_input(ACE_HANDLE fd)
{
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::handle_input>>begin\n"));
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

    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::handle_input>>end\n"));
    return 0;
}

int iMapMsgHandle::handle_timeout(const ACE_Time_Value &current_time, const void *act)
{
    
}

int iMapMsgHandle::handle_output(ACE_HANDLE)
{
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::handle_output>>begin\n"));
    bool bIsQuitLoop = true;
    while (true)
    {
        ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::handle_output>>while begin\n"));
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

    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::handle_output>>end\n"));
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
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::SendExternalCmdMsg>>begin\n"));
    string strMsg = pCmdMsg->serialize();
    int recv_cnt = this->m_socketPeer.send_n(strMsg.c_str(), strMsg.size());
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::SendExternalCmdMsg>>end\n"));
}

void iMapMsgHandle::SendInternalCmdMsg(iMapCmdMsg *pCmdMsg, int nlength)
{
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::SendInternalCmdMsg>>begin\n"));
    ACE_Message_Block*  mb1 = new ACE_Message_Block(nlength, ACE_Message_Block::MB_DATA);
    mb1->copy((char*)pCmdMsg, sizeof(nlength));

    int result1 = m_mqCmdMsg.enqueue(mb1);
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::SendInternalCmdMsg>>end\n"));
}

void iMapMsgHandle::RecvExternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::RecvExternalCmdMsg>>begin\n"));
    m_iMapCmdMsg.push_front(pCmdMsg);
    m_MsgCond.signal();
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::RecvExternalCmdMsg>>end\n"));
}

void iMapMsgHandle::RecvInternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::RecvInternalCmdMsg>>begin\n"));
    m_iMapCmdMsg.push_front(pCmdMsg);
    m_MsgCond.signal();
    ACE_DEBUG((LM_DEBUG, "iMapMsgHandle::RecvInternalCmdMsg>>end\n"));
}
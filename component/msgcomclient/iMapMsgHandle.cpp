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
    if (NULL != m_instance)
    {
        delete m_instance;
        m_instance = NULL;
    }
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
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::open>>register_handler:READ_MASK,WRITE_MASK\n"));

    
    ACE_INET_Addr addr(PORT_NO, HOSTNAME);
    ACE_Time_Value timeout(5, 0);
    if (m_connector.connect(m_socketPeer, addr, &timeout) != 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::open>>connecetd fail\n"));
        return false;
    }
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK);
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::WRITE_MASK);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::open>>connecetd entablish!\n"));

    activate();

    return 0;
}

ACE_HANDLE iMapMsgHandle::get_handle(void) const
{
    return m_socketPeer.get_handle();
}

int iMapMsgHandle::close(u_long)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::close\n"));
    return 0;
}

int iMapMsgHandle::svc(void)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>begin\n"));
    while (true)
    {
        ACE_Message_Block * mb = NULL;
        m_mqCmdMsg.dequeue(mb);
        if (NULL != mb)
        {
            iMapCmdMsg *pCmdMsg = (iMapCmdMsg*)mb->base();
            delete mb;
            mb = NULL;

            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>mb->length:%d\n", mb->length()));

        }
    }
    return 0;
}

int iMapMsgHandle::handle_input(ACE_HANDLE fd)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>begin\n"));
    while (true)
    {
        //定义一个消息
        iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

        //从内核缓存区读取消息头
        char buf[2048] = { 0 };
        int revLength = m_socketPeer.recv_n(buf, pCmdMsg->GetMsgHeaderLength());
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgHandle::handle_input>>revLength:%d\n", revLength));
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgHandle::handle_input>>recv fail!\n"));
            return -1;
        }

        //序列化消息头
        string strMsgHeader(buf, revLength);
        pCmdMsg->deserializeHeader(strMsgHeader);
        pCmdMsg->display();

        //从内核缓存区读取消息体
        ACE_OS::memset(buf, 0, 2048);
        revLength = 0;
        revLength = m_socketPeer.recv_n(buf, pCmdMsg->GetMsgBodyLength());
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgHandle::handle_input>>revLength:%d\n", revLength));
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgHandle::handle_input>>recv fail!\n"));
            return -1;
        }

        //序列化消息体
        string strMsgBody(buf, revLength + 1);
        pCmdMsg->deserializeBody(strMsgBody);

        RecvCmdMsg(pCmdMsg);
        pCmdMsg->display();

        delete pCmdMsg;
        pCmdMsg = NULL;
    }

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>end\n"));
    return 0;
}

int iMapMsgHandle::handle_timeout(const ACE_Time_Value &current_time, const void *act)
{
    
}

int iMapMsgHandle::handle_output(ACE_HANDLE)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_output>>begin\n"));
    bool bIsQuitLoop = false;
    while (true)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_output>>while begin\n"));
        m_MsgCond.wait(m_MsgMutex);
        while (!m_iMapCmdMsg.empty())
        {
            iMapCmdMsg *pCmdMsg = m_iMapCmdMsg.back();
            m_iMapCmdMsg.pop_back();
            pCmdMsg->display();
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
                //结束消息循环
                bIsQuitLoop = true;
                break;
            }
        }

        if (bIsQuitLoop)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_output>>Quit Message Loop!\n"));
            break;
        }
    }

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_output>>end\n"));
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
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>begin\n"));

    string strMsgBody;
    //序列化消息体
    strMsgBody = pCmdMsg->serializeBody();
    pCmdMsg->SetMsgBodyLength(strMsgBody.size());
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>strMsgBody.size:%d\n", strMsgBody.size()));

    //序列化消息头
    string strMsgHeader;
    strMsgHeader = pCmdMsg->serializeHeader();
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>strMsgHeader.size:%d\n", strMsgHeader.size()));

    string strMsg = strMsgHeader + strMsgBody;
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>strMsg.size:%d\n", strMsg.size()));
    int recv_cnt = this->m_socketPeer.send_n(strMsg.c_str(), strMsg.size());

    delete pCmdMsg;
    pCmdMsg = NULL;

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>end\n"));
}

void iMapMsgHandle::SendInternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendInternalCmdMsg>>begin\n"));
    int nLength = pCmdMsg->GetMsgHeaderLength() + pCmdMsg->GetBody().size();
    ACE_Message_Block*  mb1 = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    mb1->copy((char*)pCmdMsg, sizeof(nLength));

    int result1 = m_mqCmdMsg.enqueue(mb1);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendInternalCmdMsg>>end\n"));
}

void iMapMsgHandle::RecvCmdMsg(iMapCmdMsg *pCmdMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::RecvInternalCmdMsg>>begin\n"));
    ACE_Guard<ACE_Thread_Mutex> guard(m_MsgMutex);
    m_iMapCmdMsg.push_front(pCmdMsg);
    m_MsgCond.signal();
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::RecvInternalCmdMsg>>end\n"));
}
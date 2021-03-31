#include "iMapConnectorHandle.h"

#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

extern MyMsgQueue g_pMsgQueue;
extern ACE_Condition<ACE_Thread_Mutex> g_mMsgCond;

iMapConnectorHandle::iMapConnectorHandle()
{

}


iMapConnectorHandle::~iMapConnectorHandle()
{
    
}

int iMapConnectorHandle::open()
{
    ACE_INET_Addr addr(PORT_NO, HOSTNAME);
    ACE_Time_Value timeout(5, 0);
    if (m_connector.connect(m_socketPeer, addr, &timeout) != 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::open>>connecetd fail\n"));
        return -1;
    }

    //ACE_Time_Value delayTime(5);
    //ACE_Time_Value interval(10);
    //ACE_Reactor::instance()->schedule_timer(this, 0, delayTime, delayTime);
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK);
    //ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::WRITE_MASK);

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::open>>connecetd entablish!\n"));
    return 0;
}

int iMapConnectorHandle::handle_timeout(const ACE_Time_Value &current_time, const void *act)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_timeout>>begin\n"));
    //static int i = 0;
    //iMapCmdMsg *pCmdMsg = new iMapCmdMsg;
    //pCmdMsg->SetMsgID(i + 1);
    //pCmdMsg->SetMsgType(REQUEST_MSG_TYPE);
    //pCmdMsg->SetBody("test");
    //cout << "iMapConnectorHandle::handle_timeout>>pCmdMsg:" << pCmdMsg << endl;
    //this->SendCmdMsgToQueue(pCmdMsg);
}

int iMapConnectorHandle::handle_input(ACE_HANDLE fd)
{
    const int BUFFER_MAX_LENGTH = 2048;
    //从内核缓存区读取消息头
    uint8_t buf[BUFFER_MAX_LENGTH] = { 0 };
    int recv_cnt = m_socketPeer.recv(buf, BUFFER_MAX_LENGTH);
    if (recv_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return -1;
    }

    if (recv_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return 0;
    }

    if (!g_pMsgQueue.parser(buf, recv_cnt))
    {
        cout << "parser msg failed!" << endl;
    }
    else
    {
        cout << "parser msg successful!" << endl;
        g_mMsgCond.signal();
    }

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
    return 0;
}

int iMapConnectorHandle::handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::handle_close>>\n"));
    ACE_Reactor::instance()->remove_handler(this, mask);
    m_socketPeer.close();
}


ACE_HANDLE iMapConnectorHandle::get_handle(void) const
{
    return m_socketPeer.get_handle();
}

void iMapConnectorHandle::SendCmdMsgToServer(MyProtoMsg *pMsg)
{
    uint8_t *pData = NULL;
    uint32_t nLength = 0;
    pData = g_pMsgQueue.encode(pMsg, nLength);

    int recv_cnt = this->m_socketPeer.send(pData, nLength);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::SendCmdMsgToServer>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
}

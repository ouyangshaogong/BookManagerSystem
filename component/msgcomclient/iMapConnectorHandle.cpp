#include "iMapConnectorHandle.h"
#include "iMapMsgHandle.h"

#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

iMapConnectorHandle::iMapConnectorHandle(iMapMsgHandle *pCmdHandle)
    :m_pCmdHandle(pCmdHandle)
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
    //����һ����Ϣ
    iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

    //���ں˻�������ȡ��Ϣͷ
    char buf[2048] = { 0 };
    int revLength = m_socketPeer.recv_n(buf, pCmdMsg->GetMsgHeaderLength());
    if (revLength <= 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapConnectorHandle::handle_input>>recv fail!revLength:%d, errno:%d\n", revLength, errno));
        return 1;
    }

    //���л���Ϣͷ
    string strMsgHeader(buf, revLength);
    pCmdMsg->deserializeHeader(strMsgHeader);
   

    //���ں˻�������ȡ��Ϣ��
    ACE_OS::memset(buf, 0, 2048);
    revLength = 0;
    revLength = m_socketPeer.recv_n(buf, pCmdMsg->GetMsgBodyLength());
    if (revLength <= 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapConnectorHandle::handle_input>>recv fail!revLength:%d, errno:%d\n", revLength, errno));
        return 1;
    }

    //���л���Ϣ��
    string strMsgBody(buf, revLength);
    pCmdMsg->deserializeBody(strMsgBody);
    if (pCmdMsg->GetMsgType() == END_MSG_TYPE)
    {
        return -1;
    }

    ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapConnectorHandle::handle_input>>nMsgType:%d\n", pCmdMsg->GetMsgType()));
    this->SendCmdMsgToQueue(pCmdMsg);

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

void iMapConnectorHandle::SendCmdMsgToServer(iMapCmdMsg *pCmdMsg)
{
    //���л���Ϣ��
    string strMsgBody = pCmdMsg->serializeBody();
    pCmdMsg->SetMsgBodyLength(strMsgBody.size());
    //���л���Ϣͷ
    string strMsgHeader = pCmdMsg->serializeHeader();

    string strMsg = strMsgHeader + strMsgBody;
    int recv_cnt = this->m_socketPeer.send_n(strMsg.c_str(), strMsg.size());
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::SendCmdMsgToServer>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
}


void iMapConnectorHandle::SendCmdMsgToQueue(iMapCmdMsg *pCmdMsg)
{
    m_pCmdHandle->SendCmdMsgToQueue(pCmdMsg);
    
}
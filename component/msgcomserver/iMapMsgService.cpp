#include "iMapMsgService.h"

int iMapMsgService::open(void*)
{
    //ע��������ص�����
    activate();
    return this->reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);
}

int iMapMsgService::close(u_long)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::svc>>\n"));
    return 0;
}

int iMapMsgService::svc(void)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::svc>>\n"));
    return 0;
}

ACE_SOCK_Stream& iMapMsgService::peer()
{
    return this->m_sockStream;
}

ACE_HANDLE iMapMsgService::get_handle(void) const
{ 
    return this->m_sockStream.get_handle();
}

int iMapMsgService::handle_input(ACE_HANDLE fd)
{
    while (true)
    {
        //����һ����Ϣ
        iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

        //���ں˻�������ȡ��Ϣͷ
        char buf[2048] = { 0 };
        int revLength = peer().recv_n(buf, pCmdMsg->GetMsgHeaderLength());
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>recv fail!\n"));
            return -1;
        }

        //���л���Ϣͷ
        string strMsgHeader(buf, revLength);
        pCmdMsg->deserializeHeader(strMsgHeader);

        //���ں˻�������ȡ��Ϣ��
        ACE_OS::memset(buf, 0, 2048);
        revLength = 0;
        revLength = peer().recv_n(buf, pCmdMsg->GetMsgBodyLength());
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>recv fail!\n"));
            return -1;
        }

        //���л���Ϣ��
        string strMsgBody(buf, revLength);
        pCmdMsg->deserializeBody(strMsgBody);
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>nMsgID:%d, nMsgType:%d\n", pCmdMsg->GetMsgID(), pCmdMsg->GetMsgType()));

        delete pCmdMsg;
        pCmdMsg = NULL;

        //ԭ�����ͻ�ȥ
        /*string strMsg = strMsgHeader + strMsgBody;
        int nSend = peer().send_n(strMsg.c_str(), strMsg.size());
        if (nSend < 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>send fail!\n"));
            return -1;
        }*/
        
    }

    

    ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>send success!\n"));

    return 0;
}

// �ͷ���Ӧ��Դ
int iMapMsgService::handle_close(ACE_HANDLE, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
        return 0;
    mask = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, mask);
    this->m_sockStream.close();
    delete this;    //socket����ʱ�����Զ�ɾ���ÿͻ��ˣ��ͷ���Ӧ��Դ
    return 0;
}
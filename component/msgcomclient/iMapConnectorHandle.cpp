#include "iMapConnectorHandle.h"


#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

extern ACE_Thread_Mutex g_mqMutex;
extern iMapMsgQueue g_MQ;

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

    ACE_Time_Value delayTime(5);
    ACE_Time_Value interval(10);
    ACE_Reactor::instance()->schedule_timer(this, 0, delayTime, delayTime);
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK);
    //ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::WRITE_MASK);

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::open>>connecetd entablish!\n"));
    return 0;
}

int iMapConnectorHandle::handle_timeout(const ACE_Time_Value &current_time, const void *act)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_timeout>>begin\n"));
    static int i = 0;
    iMapCmdMsg *pCmdMsg = new iMapCmdMsg;
    pCmdMsg->SetMsgID(i + 1);
    pCmdMsg->SetMsgType(REQUEST_MSG_TYPE);
    pCmdMsg->SetBody("test");
    cout << "iMapConnectorHandle::handle_timeout>>pCmdMsg:" << pCmdMsg << endl;
    this->RecvCmdMsg(pCmdMsg);
}

int iMapConnectorHandle::handle_input(ACE_HANDLE fd)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::handle_input>>begin\n"));
    while (true)
    {
        //定义一个消息
        iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

        //从内核缓存区读取消息头
        char buf[2048] = { 0 };
        int revLength = m_socketPeer.recv_n(buf, pCmdMsg->GetMsgHeaderLength());
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapConnectorHandle::handle_input>>revLength:%d\n", revLength));
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapConnectorHandle::handle_input>>recv fail!\n"));
            return -1;
        }

        //序列化消息头
        string strMsgHeader(buf, revLength);
        pCmdMsg->deserializeHeader(strMsgHeader);

        //从内核缓存区读取消息体
        ACE_OS::memset(buf, 0, 2048);
        revLength = 0;
        revLength = m_socketPeer.recv_n(buf, pCmdMsg->GetMsgBodyLength());
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapConnectorHandle::handle_input>>revLength:%d\n", revLength));
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapConnectorHandle::handle_input>>recv fail!\n"));
            return -1;
        }

        //序列化消息体
        string strMsgBody(buf, revLength + 1);
        pCmdMsg->deserializeBody(strMsgBody);

        this->RecvCmdMsg(pCmdMsg);
        pCmdMsg->display("iMapConnectorHandle::handle_input");

        delete pCmdMsg;
        pCmdMsg = NULL;
    }

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::handle_input>>end\n"));
    return 0;
}

ACE_HANDLE iMapConnectorHandle::get_handle(void) const
{
    return m_socketPeer.get_handle();
}

void iMapConnectorHandle::SendExternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::SendExternalCmdMsg>>begin\n"));

    string strMsgBody;
    //序列化消息体
    strMsgBody = pCmdMsg->serializeBody();
    pCmdMsg->SetMsgBodyLength(strMsgBody.size());
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::SendExternalCmdMsg>>strMsgBody.size:%d\n", strMsgBody.size()));

    //序列化消息头
    string strMsgHeader;
    strMsgHeader = pCmdMsg->serializeHeader();
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::SendExternalCmdMsg>>strMsgHeader.size:%d\n", strMsgHeader.size()));

    string strMsg = strMsgHeader + strMsgBody;
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>strMsg.size:%d\n", strMsg.size()));
    int recv_cnt = this->m_socketPeer.send_n(strMsg.c_str(), strMsg.size());

    delete pCmdMsg;
    pCmdMsg = NULL;

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::SendExternalCmdMsg>>end\n"));
}


void iMapConnectorHandle::RecvCmdMsg(iMapCmdMsg *pCmdMsg)
{
    cout << "iMapConnectorHandle::enqueue>>pCmdMsg:" << pCmdMsg << endl;
    ACE_Guard<ACE_Thread_Mutex> guard(g_mqMutex);
    int nLength = pCmdMsg->GetMsgHeaderLength() + pCmdMsg->GetBody().length();
    ACE_Message_Block*  pMsgBlock = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    pMsgBlock->copy((char*)pCmdMsg, sizeof(nLength));
    int nRet = g_MQ.enqueue(pMsgBlock); //等待到达低水位

    if (0 >= nRet)
    {
        delete pMsgBlock;
        pMsgBlock = NULL;

        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>center is full....\n"));
    }
    else
    {
        //ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendExternalCmdMsg>>enqueue success.....\n"));
    }
}
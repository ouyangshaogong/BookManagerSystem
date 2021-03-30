#include "iMapConnectorHandle.h"
#include "MsgClientTask.h"

#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

iMapConnectorHandle::iMapConnectorHandle(TaskMgrApp *pTaskMgrApp, int nSendProc, int nTaskMgrID, TaskID nTaskID)
    :m_pTaskMgrApp(pTaskMgrApp), m_nMsgID(1)
{
    m_protoMsg.Header.nMsgID = m_nMsgID;
    m_protoMsg.Header.nMsgType = REQUEST_MSG_TYPE;
    m_protoMsg.Header.nSendProc = nSendProc;
    m_protoMsg.Header.nTaskMgrID = nTaskMgrID;
    m_protoMsg.Header.nTaskID = nTaskID;
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

    if (!m_protoDecode.parser(buf, recv_cnt))
    {
        cout << "parser msg failed!" << endl;
    }
    else
    {
        cout << "parser msg successful!" << endl;
    }

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));

    MyProtoMsg* pMsg = NULL;
    while(!m_protoDecode.empty())
    {
        pMsg = m_protoDecode.front();
        SendCmdMsgToTask(pMsg);
        m_protoDecode.pop();
    }

    

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

void iMapConnectorHandle::SendCmdMsgToServer(uint8_t* pData, int nLength)
{
    int recv_cnt = this->m_socketPeer.send(pData, nLength);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::SendCmdMsgToServer>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
}


void iMapConnectorHandle::SendCmdMsgToTask(MyProtoMsg* pMsg)
{
    TaskMgr *pTaskMgr = m_pTaskMgrApp->GetTaskMgr(pMsg->Header.nTaskMgrID);
    MsgClientTask *pTask = pTaskMgr->GetTask(pMsg->Header.nTaskID);
    pTask->SendMsgToTask(pMsg);
}

void iMapConnectorHandle::CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result)
{
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nCmdMsg = nCmdMsg;
    //根据MrbCmd判断
    m_protoMsg.Header.nRecvProc = 0;

    uint32_t nLength = 0;
    uint8_t* pData = NULL;
    pData = m_protoEncode.encode(&m_protoMsg, nLength);
    SendCmdMsgToServer(pData, nLength);

    TaskMgr *pTaskMgr = m_pTaskMgrApp->GetTaskMgr(m_protoMsg.Header.nTaskMgrID);
    Task *pTask = pTaskMgr->GetTask(m_protoMsg.Header.nTaskID);
    pTask->WaitSignal();
    pTask->GetResultValue(result);
}

Json::Value& iMapConnectorHandle::CallMethod(int nCmdMsg, const Json::Value &parameter)
{

}
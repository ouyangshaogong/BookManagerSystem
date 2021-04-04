#include "MyMsgServer.h"

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

ACE_Thread_Mutex MyMsgServer::m_mutex;
MyMsgServer* MyMsgServer::m_instance = NULL;

MyMsgServer::MyMsgServer()
{
    
}

MyMsgServer::~MyMsgServer()
{

}

MyMsgServer* MyMsgServer::Instance()
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new MyMsgServer;
        }
    }
    
    return m_instance;
}

void MyMsgServer::DispatchMessage(MyProtoMsg* pMsg)
{
    if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
    {
        SendCmdMsgToTask(pMsg);
    }
    else if(pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::StartMsgLoop>>MsgType Is RESPONSE_MSG_TYPE!\n"));
        SendCmdMsgToServer(pMsg);
    }
}


void MyMsgServer::SendCmdMsgToTask(MyProtoMsg* pMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgServiceHandle::HandleRequestMessage>>\n"));
    TaskMgr *pTaskMgr = m_pTaskMgrApp->GetTaskMgr(pMsg->Header.nTaskMgrID);
    Task *pTask = pTaskMgr->GetTask(pMsg->Header.nTaskID);
    pTask->SendMsgToTask(pMsg);
}


int MyMsgServer::SendCmdMsgToServer(MyProtoMsg* pMsg)
{
    uint8_t *pData = NULL;
    uint32_t length = 0;
    pData = encode(pMsg, length);
    string strPort = to_string(pMsg->Header.nPort);
    string strIPInfo = pMsg->Header.strIP + ":" + strPort;
    map<string, ACE_SOCK_Stream*>::iterator iter = m_IPMapSockPeer.find(strIPInfo);
    if (iter != m_IPMapSockPeer.end())
    {
        int send_cnt = iter->second->send_n(pData, length);
        if (send_cnt == 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::SendCmdMsgToServer>>send_cnt:%d, errno:%d\n", send_cnt, errno));
            return -1;
        }

        if (send_cnt < 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::SendCmdMsgToServer>>send_cnt:%d, errno:%d\n", send_cnt, errno));
            return 0;
        }
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::SendCmdMsgToServer>>send_cnt:%d, errno:%d\n", send_cnt, errno));
    }
}


#include "MyMsgServer.h"

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

ACE_Thread_Mutex MyMsgServer::m_mutex;
MyMsgServer* MyMsgServer::m_instance = NULL;

MyMsgServer::MyMsgServer(TaskMgrApp *pTaskMgrApp)
{
    m_pTaskMgrApp = pTaskMgrApp;
}

MyMsgServer::~MyMsgServer()
{

}

MyMsgServer* MyMsgServer::Instance(TaskMgrApp *pTaskMgrApp)
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new MyMsgServer(pTaskMgrApp);
        }
    }
    
    return m_instance;
}


void MyMsgServer::StartMsgLoop()
{
    MyProtoMsg* pMsg = NULL;
    while(GetMessage(pMsg))
    {
        DispatchMessage(pMsg);
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgClient::StartMsgLoop>>\n"));
    }

}

void MyMsgServer::DispatchMessage(MyProtoMsg* pMsg)
{
    if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
    {
        this->HandleRequestMessage(pMsg);
    }
    else if(pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::StartMsgLoop>>MsgType Is Error!\n"));
        SendCmdMsgToServer(pMsg);
    }
}

void MyMsgServer::HandleRequestMessage(MyProtoMsg* pMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgClient::HandleRequestMessage>>\n"));
    TaskMgr *pTaskMgr = m_pTaskMgrApp->GetTaskMgr(pMsg->Header.nTaskMgrID);
    Task *pTask = pTaskMgr->GetTask(pMsg->Header.nTaskID);
    pTask->SendMsgToTask(pMsg);
}
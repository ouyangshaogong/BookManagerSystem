#include "MsgClientTaskMgrApp.h"

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

MyMsgQueue g_pMsgQueue;
ACE_Thread_Mutex g_mMsgMutex;
ACE_Condition<ACE_Thread_Mutex> g_mMsgCond(g_mMsgMutex);

ACE_Thread_Mutex MsgClientTaskMgrApp::m_mutex;
MsgClientTaskMgrApp* MsgClientTaskMgrApp::m_instance = NULL;

MsgClientTaskMgrApp::MsgClientTaskMgrApp()
{

}

MsgClientTaskMgrApp::~MsgClientTaskMgrApp()
{

}

MsgClientTaskMgrApp* MsgClientTaskMgrApp::Instance()
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new MsgClientTaskMgrApp();
        }
    }
    
    return m_instance;
}

int MsgClientTaskMgrApp::open()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTaskMgrApp::open>>begin\n"));
    
    activate();
    return 0;
}

int MsgClientTaskMgrApp::close()
{
    return 0;
}

int MsgClientTaskMgrApp::svc()
{
    m_ConnectorHandle.open();
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTaskMgrApp::svc\n"));
    while (true)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTaskMgrApp::svc>>handle_events\n"));
        ACE_Reactor::instance()->handle_events();
    }

    return 0;
}

void MsgClientTaskMgrApp::StartMsgLoop()
{
    while(true)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTaskMgrApp::StartMsgLoop>>while(true)\n"));
        if (g_pMsgQueue.empty())
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTaskMgrApp::StartMsgLoop>>g_mMsgCond\n"));
            g_mMsgCond.wait();
        }
        
        MyProtoMsg* pMsg = NULL;
        while (!g_pMsgQueue.empty())
        {
            pMsg = g_pMsgQueue.front();
            if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
            {
                m_ConnectorHandle.SendCmdMsgToServer(pMsg);
            }
            else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
            {
                TaskMgr *pTaskMgr = this->GetTaskMgr(pMsg->Header.nTaskMgrID);
                Task *pTask = pTaskMgr->GetTask(pMsg->Header.nTaskID);
                pTask->SendSignal(pMsg);
            }
            else
            {
                ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::StartMsgLoop>>MsgType Is Error!\n"));
            }

            g_pMsgQueue.pop();
        }
        
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTaskMgrApp::StartMsgLoop>>\n"));
    }

}
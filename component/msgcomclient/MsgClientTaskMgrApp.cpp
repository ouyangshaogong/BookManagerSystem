#include "MsgClientTaskMgrApp.h"

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

MyMsgQueue g_pMsgQueue;
ACE_Thread_Mutex g_mMsgMutex;
ACE_Condition<ACE_Thread_Mutex> g_mMsgCond(g_mMsgMutex);

int MsgClientTaskMgrApp::InitProcessEnv(ACE_Thread_Manager *pThrMgr)
{
    m_pThrMgr = pThrMgr;
    return 0;
}

int MsgClientTaskMgrApp::open()
{
    activate();
    return 0;
}

int MsgClientTaskMgrApp::close()
{
    return 0;
}

int MsgClientTaskMgrApp::svc()
{
    while (true)
    {
        ACE_Reactor::instance()->handle_events();
    }

    return 0;
}

void MsgClientTaskMgrApp::StartMsgLoop()
{
    while(true)
    {
        if (g_pMsgQueue.empty())
        {
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
    }

}
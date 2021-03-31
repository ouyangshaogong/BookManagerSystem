#include "TaskMgrApp.h"

TaskMgrApp::TaskMgrApp()
{
    m_nGlobalTaskMgrID = 1;
    m_pThrMgr = NULL;
}


TaskMgrApp::~TaskMgrApp()
{
}

int TaskMgrApp::InitProcessEnv(ACE_Thread_Manager *pThrMgr)
{
    m_pThrMgr = pThrMgr;

    return 0;
}

int TaskMgrApp::open()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::open>>begin\n"));
    return 0;
}

int TaskMgrApp::close()
{
    return 0;
}

int TaskMgrApp::svc()
{

    return 0;
}

int TaskMgrApp::GetGlobalTaskMgrID()
{
    return m_nGlobalTaskMgrID;
}

int TaskMgrApp::InsertTaskMgr(TaskMgr* pTaskMgr)
{
    m_nIdMapTaskMgr.insert(map<int, TaskMgr*>::value_type(m_nGlobalTaskMgrID, pTaskMgr));
    m_nGlobalTaskMgrID++;
    return 0;
}

TaskMgr* TaskMgrApp::GetTaskMgr(int nTaskMgrID)
{
    map<int, TaskMgr*>::iterator iter = m_nIdMapTaskMgr.find(nTaskMgrID);
    if (iter != m_nIdMapTaskMgr.end())
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::TaskMgrApp::putq succeed!\n"));
        return iter->second;
    }

    return NULL;
}

void TaskMgrApp::StartMsgLoop()
{

}

void TaskMgrApp::ExitThread()
{
    m_pThrMgr->wait();
}

void TaskMgrApp::TaskMgrDestory()
{
    map<int, TaskMgr*>::iterator iter = m_nIdMapTaskMgr.begin();
    for (; iter != m_nIdMapTaskMgr.end(); ++iter)
    {
        iter->second->DestoryTask();
        delete iter->second;
        iter->second = NULL;
    }

    m_nIdMapTaskMgr.clear();
}
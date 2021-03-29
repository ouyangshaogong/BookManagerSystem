#include "TaskMgrApp.h"

ACE_Thread_Mutex TaskMgrApp::m_mutex;
TaskMgrApp *TaskMgrApp::m_instance = NULL;

TaskMgrApp::TaskMgrApp()
{
    m_pThrMgr = NULL;
}


TaskMgrApp::~TaskMgrApp()
{
}

TaskMgrApp* TaskMgrApp::Instance()
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new TaskMgrApp();
        }
    }
    return m_instance;
}

int TaskMgrApp::InitProcessEnv(ACE_Thread_Manager *pThrMgr)
{
    m_pThrMgr = pThrMgr;

    return 0;
}

int TaskMgrApp::InsertTaskMgr(TaskMgr* pTaskMgr)
{
    int nTaskMgrID = pTaskMgr->GetTaskMgrID();
    m_nIdMapTaskMgr.insert(map<int, TaskMgr*>::value_type(nTaskMgrID, pTaskMgr));
}

TaskMgr* TaskMgrApp::GetTaskMgr(int nTaskMgrID)
{
    map<int, TaskMgr*>::iterator iter = m_nIdMapTaskMgr.find(nTaskMgrID);
    if (iter != m_nIdMapTaskMgr.end())
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::TaskMgrApp::putq succeed!\n"));
        return iter->second;
    }
}

void TaskMgrApp::StartMsgLoop()
{
    while (true)
    {
        ACE_Reactor::instance()->handle_events();
    }

    //等待线程退出
    ACE_Thread_Manager::instance()->wait();
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
    }

    m_nIdMapTaskMgr.clear();
}
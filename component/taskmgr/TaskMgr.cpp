#include "TaskMgr.h"

#define TASK_MGR_MAX_VALUE 256

TaskMgr::TaskMgr()
{
    m_nGlobalTaskID = 1;
}


TaskMgr::~TaskMgr()
{
}

int TaskMgr::InitEnv(int nThreadNum, int nTaskMgrID)
{
    if (nTaskMgrID > TASK_MGR_MAX_VALUE)
    {
        return -1;
    }

    m_nTaskMgrID = nTaskMgrID;
    m_nThreadNum = nTaskMgrID;
    if (nThreadNum > TASK_MAX_VALUE)
    {
        m_nThreadNum = TASK_MAX_VALUE;
    }

    open();
    return 0;
}

int TaskMgr::open()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgr::open>>\n"));
    activate(THR_NEW_LWP, m_nThreadNum);
    return 0;
}

void TaskMgr::InsertTask(Task *pTask)
{
    m_nIDMapTask.insert(map<TaskID, Task*>::value_type(m_nGlobalTaskID, pTask));
    m_nGlobalTaskID++;
}

void TaskMgr::DestoryTask()
{
    map<int, Task*>::iterator iter = m_nIDMapTask.begin();
    for (; iter != m_nIDMapTask.end(); ++iter)
    {
        //delete iter->second;
        iter->second = NULL;
    }
    
    m_nIDMapTask.clear();

}

int TaskMgr::close()
{
    return 0;
}

int TaskMgr::svc()
{
    return 0;
}

Task* TaskMgr::GetTask(TaskID nTaskID)
{
    map<TaskID, Task*>::iterator iter = m_nIDMapTask.find(nTaskID);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgr::GetTask>>m_nIDMapTask.size:%d\n", m_nIDMapTask.size()));
    if (iter != m_nIDMapTask.end())
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgr::GetTask>>Task*:%d\n", iter->second));
        return (Task*)iter->second;
    }
    
    return NULL;
}

TaskID TaskMgr::GetGlobalTaskID()
{
    return m_nGlobalTaskID;
}

TaskMgrID TaskMgr::GetLocalTaskMgrID()
{
    return m_nTaskMgrID;
}

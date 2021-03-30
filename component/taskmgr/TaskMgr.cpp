#include "TaskMgr.h"

#define TASK_MGR_MAX_VALUE 256

TaskMgr::TaskMgr()
{
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

    return 0;
}

int TaskMgr::open(int nThreadNum)
{
    activate(THR_NEW_LWP, nThreadNum);
}

void TaskMgr::InsertTask(Task *pTask)
{
    m_nIDMapTask.insert(map<TaskID, Task*>::value_type(m_nGlobalTaskID, pTask));
    m_nGlobalTaskID++;
}

void TaskMgr::InsertTask(Task *task)
{
    task->open(m_nThreadNum);
    m_taskList.push_back(task);
}

void TaskMgr::DestoryTask()
{
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
    if (iter != m_nIDMapTask.end())
    {
        return iter->second;
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

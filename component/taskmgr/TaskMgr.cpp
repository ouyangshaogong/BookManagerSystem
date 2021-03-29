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
    activate();
}

void TaskMgr::InsertTask(Task *task)
{
    task->open(m_nThreadNum);
    m_taskList.push_back(task);
}

void TaskMgr::DestoryTask()
{
    m_taskList.clear();
}

int TaskMgr::close()
{
    return 0;
}

int TaskMgr::svc()
{
    return 0;
}

int TaskMgr::GetTaskMgrID()
{
    return m_nTaskMgrID;
}

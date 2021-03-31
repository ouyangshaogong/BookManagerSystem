#include "Task.h"

Task::Task()
{
}


Task::~Task()
{
}

int Task::InitEnv(int nThreadNum, TaskID nTaskID)
{
    m_nTaskID = nTaskID;
    m_nThreadNum = nThreadNum;
    return 0;
}

int Task::open()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)Task::open>>\n"));
    activate(THR_NEW_LWP, m_nThreadNum);
    return 0;
}

int Task::close()
{
    return 0;
}

int Task::svc()
{

    return 0;
}

int Task::CreateDynamicTask()
{
    ACE_Thread_Manager::instance()->spawn_n(m_nThreadNum, (ACE_THR_FUNC)Task::DynamicTask, NULL);
    return 0;
}

ACE_THR_FUNC Task::DynamicTask()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)Task::DynamicTask>>\n"));
}

void Task::process(int nCmdMsg, void* InBody, void* OutBody)
{

}

TaskID Task::GetLocalTaskID()
{
    return m_nTaskID;
}

void Task::SendMsgToTask(MyProtoMsg *pMsg)
{
    
}

void Task::SendSignal(MyProtoMsg *pMsg)
{

}

MyProtoMsg* Task::WaitSignal()
{

}


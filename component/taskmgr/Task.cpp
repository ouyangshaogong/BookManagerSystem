#include "Task.h"

Task::Task()
:m_tCallMutex(), m_tCondMsg(m_tCallMutex)
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

int Task::CreateStaticTask()
{
    return open();
}

int Task::CreateDynamicTask()
{
    //ACE_Thread_Manager::instance()->spawn_n(m_nThreadNum, this->DynamicTask, NULL);
}

void Task::DynamicTask()
{

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

void Task::GetResultValue(Json::Value &value)
{

}

void Task::SendSignal()
{

}

void Task::WaitSignal()
{

}


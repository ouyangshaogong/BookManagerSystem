#include "Task.h"

Task::Task()
{
}


Task::~Task()
{
}


int Task::open(int nThreadNum)
{
    activate(THR_NEW_LWP, nThreadNum);
}

int Task::close()
{
    return 0;
}

int Task::svc()
{
    return 0;
}

void Task::process(MyProtoMsg *pInMsg, MyProtoMsg *pOutMsg)
{

}
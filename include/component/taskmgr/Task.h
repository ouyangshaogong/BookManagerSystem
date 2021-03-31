#ifndef __TASK__
#define __TASK__

#include "commonace.h"
#include "MyProtoMsg.h"

typedef int TaskID;

class Task: public ACE_Task<ACE_MT_SYNCH>
{
public:
    Task();
    virtual ~Task();

    int InitEnv(int nThreadNum, TaskID nTaskID);
    virtual int open();
    virtual int close();
    virtual int svc();
    int CreateStaticTask();
    int CreateDynamicTask();
    void DynamicTask();
    TaskID GetLocalTaskID();
    virtual void process(int nCmdMsg, void* InBody, void* OutBody);

    virtual void SendMsgToTask(MyProtoMsg *pMsg);

    virtual void GetResultValue(Json::Value &value);
    virtual void SendSignal();
    virtual void WaitSignal();

private:
    TaskID m_nTaskID;
    int m_nThreadNum;

    ACE_Thread_Mutex m_tCallMutex;
    ACE_Condition<ACE_Thread_Mutex> m_tCondMsg;
};

#endif

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
    virtual void SendSignal(MyProtoMsg *m_pMsg);
    virtual MyProtoMsg *WaitSignal();

private:
    TaskID m_nTaskID;
    int m_nThreadNum;

    
};

#endif

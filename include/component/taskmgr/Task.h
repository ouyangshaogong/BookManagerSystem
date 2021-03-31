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
    virtual int CreateStaticTask();
    virtual int CreateDynamicTask();
    static ACE_THR_FUNC DynamicTask();
    TaskID GetLocalTaskID();
    virtual void process(int nCmdMsg, void* InBody, void* OutBody);

    virtual void SendMsgToTask(MyProtoMsg *pMsg);
    virtual void SendSignal(MyProtoMsg *pMsg);
    virtual MyProtoMsg *WaitSignal();

protected:
    TaskID m_nTaskID;
    int m_nThreadNum;

    
};

#endif

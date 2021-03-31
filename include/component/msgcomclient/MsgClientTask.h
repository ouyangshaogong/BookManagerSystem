#ifndef __MSG_CLIENT_TASK__
#define __MSG_CLIENT_TASK__

#include "commonace.h"
#include "MyProtoMsg.h"
#include "Task.h"

typedef int TaskID;

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

class MsgClientTask: public Task
{
public:
    MsgClientTask();
    virtual ~MsgClientTask();
    
    virtual int svc();
    
    virtual void process(int nCmdMsg, Json::Value InBody, Json::Value OutBody);

    static ACE_THR_FUNC DynamicTask();

    virtual int CreateDynamicTask();
    
    void SendMsgToTask(MyProtoMsg *pMsg);

    void SendSignal(MyProtoMsg *m_pMsg);
    MyProtoMsg *WaitSignal();

private:

    int m_nMsgID;
    int m_nSendProc;

    MyProtoMsg *m_pMsg;

    ACE_Thread_Mutex m_tCallMutex;
    ACE_Condition<ACE_Thread_Mutex> m_tCondMsg;
};

#endif

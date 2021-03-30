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

    virtual void process(int nCmdMsg, Json::Value InBody, Json::Value OutBody);

    void SendMsgToTask(MyProtoMsg *pMsg);

    void GetResultValue(Json::Value &value);
    void SendSignal();
    void WaitSignal();

private:

    int m_nMsgID;
    int m_nSendProc;

    MyProtoDecode m_protoDecode;
    MyProtoEncode m_protoEncode;
    MyProtoMsg m_protoMsg;

    ACE_Thread_Mutex m_callMutex;
    ACE_Condition<ACE_Thread_Mutex> m_condMsg;
};

#endif

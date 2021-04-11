#ifndef __MY_MSG_SERVER_TASK__
#define __MY_MSG_SERVER_TASK__

#include "commonace.h"
#include "MyProtoMsg.h"
#include "Task.h"
#include "MyMsgClient.h"
#include "MyMsgServer.h"

typedef int TaskID;

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

class MyMsgServerTask: public Task
{
public:
    MyMsgServerTask(MyMsgServer *pMsgServer);
    virtual ~MyMsgServerTask();

    virtual int open();
    virtual int svc();
    
    virtual void process(int nCmdMsg, Json::Value &InBody, Json::Value &OutBody);

    static ACE_THR_FUNC DynamicTask(void* arg);

    virtual int CreateDynamicTask(MyMsgClient *pMrbMsgClient);
    
    void SendMsgToTask(MyProtoMsg *pMsg);

private:

    int m_nMsgID;
    int m_nSendProc;
    MyMsgServer *m_pMsgServer;

    //static MyMsgClient m_mrbMsgClient; 
};

#endif

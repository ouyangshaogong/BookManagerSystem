#ifndef __MY_MSG_CLIENT__
#define __MY_MSG_CLIENT__

#include "TaskMgrApp.h"
#include "MyProtoMsg.h"
#include "MyMsgQueue.h"

class MyMsgServer: public MyMsgQueue
{
private:
    MyMsgServer(TaskMgrApp *pTaskMgrApp);

public:
    ~MyMsgServer();
    static MyMsgServer* Instance(TaskMgrApp *pTaskMgrApp);

    void StartMsgLoop();
    virtual void DispatchMessage(MyProtoMsg* pMsg);
    virtual void HandleRequestMessage(MyProtoMsg* pMsg);

private:
    TaskMgrApp *m_pTaskMgrApp;
    static ACE_Thread_Mutex m_mutex;
    static MyMsgServer *m_instance;
};

#endif

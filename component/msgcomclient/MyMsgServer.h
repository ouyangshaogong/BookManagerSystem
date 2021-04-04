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

    virtual void DispatchMessage(MyProtoMsg* pMsg);
    void SendCmdMsgToTask(MyProtoMsg* pMsg);
    int SendCmdMsgToServer(MyProtoMsg* pMsg);

    void GetSockPeer(string strIP, ACE_SOCK_Stream *pPeer);
    void DeleteSockPeer(string strIP);

private:
    static ACE_Thread_Mutex m_mutex;
    static MyMsgServer *m_instance;
    
    TaskMgrApp *m_pTaskMgrApp;
    map<string, ACE_SOCK_Stream*> m_IPMapSockPeer;
};

#endif

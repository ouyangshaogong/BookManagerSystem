#ifndef __MSG_CLIENT_TASK_MGR_APP__
#define __MSG_CLIENT_TASK_MGR_APP__

#include "TaskMgrApp.h"
#include "iMapConnectorHandle.h"


class MsgClientTaskMgrApp: public TaskMgrApp
{
private:
    MsgClientTaskMgrApp();

public:
    ~MsgClientTaskMgrApp();
    static MsgClientTaskMgrApp* Instance();

    void StartMsgLoop();
    
    virtual int open();
    virtual int close();
    virtual int svc();
    
private:
    iMapConnectorHandle m_ConnectorHandle;

    static ACE_Thread_Mutex m_mutex;
    static MsgClientTaskMgrApp *m_instance;
};

#endif

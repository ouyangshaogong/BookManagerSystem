#ifndef __MSG_CLIENT_TASK_MGR_APP__
#define __MSG_CLIENT_TASK_MGR_APP__

#include "TaskMgrApp.h"
#include "iMapConnectorHandle.h"


class MsgClientTaskMgrApp: public TaskMgrApp, public ACE_Task<ACE_MT_SYNCH>
{
private:
        MsgClientTaskMgrApp();

public:
    virtual int InitProcessEnv(ACE_Thread_Manager *pThrMgr);
    void StartMsgLoop();
    
    virtual int open();
    virtual int close();
    virtual int svc();
    
private:
    iMapConnectorHandle m_ConnectorHandle;

    
};

#endif

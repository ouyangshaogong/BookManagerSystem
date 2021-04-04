#ifndef __MRB_BUS__
#define __MRB_BUS__

#include "commonace.h"
#include "TaskMgrApp.h"
#include "MyMsgServerTask.h"
#include "MyMsgQueue.h"
#include "MsgServiceHandle.h"

class iMapMrbBus: public ACE_Task<ACE_MT_SYNCH>
{
public:
    
    ~iMapMrbBus();

    static iMapMrbBus* Instance(TaskMgrApp *pTaskMgrApp);

    virtual int open();
    virtual int svc();
    virtual int close();

    void StartBus();
    void StartMsgLoop();
    void StopBus();

private:
    iMapMrbBus(TaskMgrApp *pTaskMgrApp);

private:
    static ACE_Thread_Mutex m_mutex;
    static iMapMrbBus *m_instance;

    TaskMgrApp *m_pTaskMgrApp;

    MsgServiceAcceptor m_acceptor;
     ACE_INET_Addr m_nInetAddr;
};

#endif

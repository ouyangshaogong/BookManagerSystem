#ifndef __MRB_BUS__
#define __MRB_BUS__

#include "commonace.h"
#include "TaskMgrApp.h"
#include "MyMsgServerTask.h"

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

    MyMsgServer *m_pMsgServer;
    TaskMgrApp *m_pTaskMgrApp;
};

#endif

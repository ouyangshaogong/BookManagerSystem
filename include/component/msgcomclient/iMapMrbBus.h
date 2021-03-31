#ifndef __MRB_BUS__
#define __MRB_BUS__

#include "commonace.h"
#include "MsgClientTaskMgrApp.h"
class iMapMrbBus
{
public:
    
    ~iMapMrbBus();

    static iMapMrbBus* Instance(TaskMgrApp *pTaskMgrApp);

    void StartBus();
    void StartMsgLoop();
    void StopBus();

private:
    iMapMrbBus(TaskMgrApp *pTaskMgrApp);

private:
    static ACE_Thread_Mutex m_mutex;
    static iMapMrbBus *m_instance;

    TaskMgrApp *m_pTaskMgrApp;
};

#endif

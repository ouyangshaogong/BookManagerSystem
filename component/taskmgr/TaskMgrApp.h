#ifndef __TASK_MGR_APP__
#define __TASK_MGR_APP__

#include "ace/Thread_Manager.h"
#include "TaskMgr.h"
#include <list>
#include <map>

using namespace std;

class TaskMgrApp: public ACE_Task<ACE_MT_SYNCH>
{
public:
    TaskMgrApp();
    virtual ~TaskMgrApp();
    int InitProcessEnv(ACE_Thread_Manager *pThrMgr);
    virtual int open();
    virtual int close();
    virtual int svc();
    virtual void StartMsgLoop();

    
    int InsertTaskMgr(TaskMgr* pTaskMgr);
    TaskMgr* GetTaskMgr(int nTaskMgrID);
    
    void ExitThread();
    void TaskMgrDestory();
    int GetGlobalTaskMgrID();

protected:
    ACE_Thread_Manager *m_pThrMgr;

private:
    map<int, TaskMgr*> m_nIdMapTaskMgr;
    TaskMgrID m_nGlobalTaskMgrID;
};

#endif


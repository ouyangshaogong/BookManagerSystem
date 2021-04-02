#ifndef __TASK_MGR_APP__
#define __TASK_MGR_APP__

#include "ace/Thread_Manager.h"
#include "TaskMgr.h"
#include <list>
#include <map>

using namespace std;

class TaskMgrApp
{
public:
    TaskMgrApp();
    virtual ~TaskMgrApp();
    static TaskMgrApp* Instance();
    int InitProcessEnv(ACE_Thread_Manager *pThrMgr);

    
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

    static ACE_Thread_Mutex m_mutex;
    static TaskMgrApp *m_instance;
};

#endif


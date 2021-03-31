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
    virtual ~TaskMgrApp();

    static TaskMgrApp* Instance();
    virtual int InitProcessEnv(ACE_Thread_Manager *pThrMgr);
    int InsertTaskMgr(TaskMgr* pTaskMgr);
    TaskMgr* GetTaskMgr(int nTaskMgrID);
    virtual void StartMsgLoop();
    void ExitThread();
    void TaskMgrDestory();
    int GetGlobalTaskMgrID();
    
    
private:
    TaskMgrApp();

protected:
    ACE_Thread_Manager *m_pThrMgr;

private:
    map<int, TaskMgr*> m_nIdMapTaskMgr;
    static ACE_Thread_Mutex m_mutex;
    static TaskMgrApp *m_instance;
    

    TaskMgrID m_nGlobalTaskMgrID;
};

#endif


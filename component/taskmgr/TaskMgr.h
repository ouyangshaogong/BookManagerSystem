#ifndef __TASK_MGR__
#define __TASK_MGR__

#include "Task.h"
#include "commonace.h"


using namespace std;


const int TASK_MAX_VALUE = 256;
typedef int TaskMgrID;

class TaskMgr: public ACE_Task<ACE_MT_SYNCH>
{
public:
    TaskMgr();
    virtual ~TaskMgr();

    int InitEnv(int nThreadNum, int nTaskMgrID);

    int open(int nThreadNum);
    int close();
    int svc();

    void InsertTask(Task *task);
    void DestoryTask();

    int GetTaskMgrID();



private:
    list<Task*> m_taskList;
    TaskMgrID m_nTaskMgrID;
    int m_nThreadNum;
    bool m_nThreadState;
};


#endif


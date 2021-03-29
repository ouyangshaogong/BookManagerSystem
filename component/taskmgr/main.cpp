#include "TaskMgrApp.h"

int main()
{
    TaskMgrApp *pTaskApp = TaskMgrApp::Instance();

    int nRet = pTaskApp->InitProcessEnv(ACE_Thread_Manager::instance());
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskApp->InitProcessEnv fail!\n"));
    }

    TaskMgr* pTaskMgr = new TaskMgr();
    nRet = pTaskMgr->InitEnv(3, 1);
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskMgr->InitEnv fail!\n"));
    }

    Task *task = new Task;
    pTaskMgr->InsertTask(task);
    pTaskApp->InsertTaskMgr(pTaskMgr);

    //task->Initialize();
    //pTaskApp->StartMsgLoop();
    //task->Initialize();

    pTaskApp->ExitThread();

    pTaskApp->TaskMgrDestory();
}
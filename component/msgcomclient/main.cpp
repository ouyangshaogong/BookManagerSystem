#include "TaskMgrApp.h"
#include "iMapConnectorHandle.h"
#include "MsgClientTask.h"

int main()
{
    TaskMgrApp *pTaskApp = TaskMgrApp::Instance();

    int nRet = pTaskApp->InitProcessEnv(ACE_Thread_Manager::instance());
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskApp->InitProcessEnv fail!\n"));
    }

    TaskMgr* pTaskMgr = new TaskMgr();
    nRet = pTaskMgr->InitEnv(1);
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskMgr->InitEnv fail!\n"));
    }

    

    Task *pTaskStatic = new MsgClientTask;
    pTaskStatic->CreateStaticTask();
    pTaskStatic->InitEnv(3, pTaskMgr->GetGlobalTaskID());
    pTaskMgr->InsertTask(pTaskStatic);

    Task *pTaskDynamic = new MsgClientTask;
    pTaskDynamic->CreateDynamicTask();
    pTaskDynamic->InitEnv(3, pTaskMgr->GetGlobalTaskID());
    pTaskMgr->InsertTask(pTaskDynamic);

    pTaskApp->InsertTaskMgr(pTaskMgr);

    iMapConnectorHandle connHandle(pTaskApp, 50, pTaskMgr->GetLocalTaskMgrID(), pTaskStatic->GetLocalTaskID());
    //task->Initialize();
    pTaskApp->StartMsgLoop();
    //task->Initialize();

    pTaskApp->ExitThread();

    pTaskApp->TaskMgrDestory();
}
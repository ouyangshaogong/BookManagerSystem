#include "MsgClientTaskMgrApp.h"
#include "iMapConnectorHandle.h"
#include "MsgClientTask.h"

int main()
{
    iMapConnectorHandle connHandle;
    MsgClientTaskMgrApp *pTaskApp = MsgClientTaskMgrApp::Instance();

    int nRet = pTaskApp->InitProcessEnv(ACE_Thread_Manager::instance(), connHandle);
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskApp->InitProcessEnv fail!\n"));
    }

    TaskMgr* pTaskMgr = new TaskMgr();
    nRet = pTaskMgr->InitEnv(1, pTaskApp->GetGlobalTaskMgrID());
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

    
    //task->Initialize();
    pTaskApp->StartMsgLoop();
    //task->Initialize();

    pTaskApp->ExitThread();

    pTaskApp->TaskMgrDestory();
}
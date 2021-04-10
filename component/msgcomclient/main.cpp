#include "iMapMrbBus.h"
#include "MyMsgClient.h"
#include "TaskMgrApp.h"

MyMsgClient mrbMsgClient;


ACE_THR_FUNC Work(void *arg)
{
    ACE_OS::sleep(5);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)Work>>\n"));
    mrbMsgClient.SetMsgValue(SEND_PROC_ID, 1, 1);
    for (int i = 0; i< 10; i++)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTask::DynamicTask>>\n"));
        Json::Value InParam;
        InParam["test"] = "test";

        Json::Value OutParam;
        mrbMsgClient.CallMethod(i + 1, InParam, OutParam);
    }
    
     return 0;
}


int main()
{
    ACE_Thread_Manager::instance()->spawn_n(1, (ACE_THR_FUNC)Work, NULL);
    TaskMgrApp *pTaskMgrApp = TaskMgrApp::Instance();
    iMapMrbBus *pMrbBus = iMapMrbBus::Instance(pTaskMgrApp);

    pMrbBus->open();
    pMrbBus->StartBus();
    pMrbBus->StartMsgLoop();
    pMrbBus->StopBus();
}

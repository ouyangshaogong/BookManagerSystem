#include "iMapMrbBus.h"
#include "MyMsgClient.h"
#include "TaskMgrApp.h"

ACE_THR_FUNC Work(void *arg)
{
    ACE_OS::sleep(5);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)Work>>\n"));

    MyMsgClient mrbMsgClient; 
    mrbMsgClient.SetMsgValue(50, 1, 1);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTask::DynamicTask>>\n"));
    Json::Value InParam;
    InParam["test"] = "test";

    Json::Value OutParam;
    mrbMsgClient.CallMethod(1, InParam, OutParam);
     return 0;
}


int main()
{
    ACE_Thread_Manager::instance()->spawn_n(1, (ACE_THR_FUNC)Work, NULL);
    TaskMgrApp *pTaskMgrApp = TaskMgrApp::Instance();
    iMapMrbBus *pMrbBus = iMapMrbBus::Instance(pTaskMgrApp);

    pMrbBus->StartBus();
    pMrbBus->StartMsgLoop();
    pMrbBus->StopBus();
}

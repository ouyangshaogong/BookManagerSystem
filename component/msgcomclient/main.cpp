#include "iMapMrbBus.h"
#include "MrbMsgClient.h"


ACE_THR_FUNC Work(void *arg)
{
    ACE_OS::sleep(5);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)Work>>\n"));

    for (int i = 0; i < 5; i++)
    {
        //MrbMsgClient mrbMsgClient; 
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTask::DynamicTask>>\n"));
        Json::Value InParam;
        InParam["test"] = "test";

        Json::Value OutParam;
        //mrbMsgClient.CallMethod(i, InParam, OutParam);
    }
     return 0;
}


int main()
{
    //ACE_Thread_Manager::instance()->spawn_n(1, (ACE_THR_FUNC)Work, NULL);
    MsgClientTaskMgrApp *pTaskMgrApp = MsgClientTaskMgrApp::Instance();
    iMapMrbBus *pMrbBus = iMapMrbBus::Instance(pTaskMgrApp);

    pMrbBus->StartBus();
    pMrbBus->StartMsgLoop();
    pMrbBus->StopBus();
}

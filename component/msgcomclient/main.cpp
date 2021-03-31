#include "iMapMrbBus.h"

int main()
{
    MsgClientTaskMgrApp *pTaskMgrApp = MsgClientTaskMgrApp::Instance();
    iMapMrbBus *pMrbBus = iMapMrbBus::Instance(pTaskMgrApp);

    pMrbBus->StartBus();
    pMrbBus->StartMsgLoop();
    pMrbBus->StopBus();
}

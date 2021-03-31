#include "iMapMrbBus.h"

int main()
{
    TaskMgrApp *pTaskMgrApp = TaskMgrApp::Instance();
    iMapMrbBus *pMrbBus = iMapMrbBus::Instance(pTaskMgrApp);

    pMrbBus->StartBus();
    pMrbBus->StartMsgLoop();
    pMrbBus->StopBus();
}

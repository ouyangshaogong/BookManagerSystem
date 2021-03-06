#include "DataController.h"
#include "DataProxy.h"
#include "commonfunc.h"

extern CommonFunc g_commonFunc;

void DataController::handleEvent(NotifyMsg notify)
{
    DataProxy *dataProxy = (DataProxy*)CommonFunc::Instance()->RetrieveProxy(notify.strClassName);
    dataProxy->AddLevel(50);
}

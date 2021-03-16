#include "DataController.h"
#include "DataProxy.h"
#include "datacommonfunc.h"

void DataController::handleEvent(NotifyController notify)
{
    DataProxy *dataProxy = (DataProxy*)DataCommonFunc::Instance()->RetrieveProxy(notify.strClassName);
    dataProxy->AddLevel(50);
}

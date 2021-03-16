#include "DataController.h"
#include "DataProxy.h"
#include "commonfunc.h"

void DataController::handleEvent(NotifyController notify)
{
    DataProxy *dataProxy = (DataProxy*)RetrieveProxy(notify.strClassName);
    dataProxy->AddLevel(50);
}

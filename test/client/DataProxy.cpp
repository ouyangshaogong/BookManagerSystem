#include "DataProxy.h"
#include "commonfunc.h"

#define MSG_ADDLEVEL 1000
void DataProxy::AddLevel(int nLevel)
{
    int level = dataModel.GetLevel();
    dataModel.SetLevel(level + nLevel);

    level = dataModel.GetLevel();
    SendNotifyCationToView(MSG_ADDLEVEL, &level);
}
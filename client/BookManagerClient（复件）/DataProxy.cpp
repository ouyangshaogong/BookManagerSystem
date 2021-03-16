#include "DataProxy.h"
#include "datacommonfunc.h"

#define MSG_ADDLEVEL 1000
void DataProxy::AddLevel(int nLevel)
{
    int level = dataModel.GetLevel();
    dataModel.SetLevel(level + nLevel);

    level = dataModel.GetLevel();
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_ADDLEVEL, &level);
}

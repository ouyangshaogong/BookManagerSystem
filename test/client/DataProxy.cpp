#include "DataProxy.h"

void DataProxy::AddLevel(int nLevel)
{
    int level = dataModel.GetLevel();
    dataModel.SetLevel(level + nLevel);

    
}
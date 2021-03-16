#ifndef __DATA_PROXY__
#define __DATA_PROXY__

#include "proxy.h"
#include "DataModel.h"

class DataProxy: public Proxy
{
public:
    DataProxy():Proxy("DataProxy"){};

    void AddLevel(int nLevel);

private:
    DataModel dataModel;
};

#endif
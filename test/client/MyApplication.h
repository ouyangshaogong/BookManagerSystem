#ifndef __MY_APPLICATION__
#define __MY_APPLICATION__

#include "application.h"
#include "DataController.h"
#include "DataProxy.h"
#include "DataView.h"

class MyApplication: public Application
{
public:
    virtual void StartApp(void *pApp);
};

#endif
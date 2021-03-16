#ifndef __MY_APPLICATION__
#define __MY_APPLICATION__

#include "application.h"
#include "DataController.h"
#include "DataProxy.h"
#include "widget.h"

class MyApplication: public Application
{
public:
    MyApplication(){}
    virtual void StartApp(void *pApp);
};

#endif

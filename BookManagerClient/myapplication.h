#ifndef __MY_APPLICATION__
#define __MY_APPLICATION__

#include "application.h"
#include "datacontroller.h"
#include "dataproxy.h"
#include "mainwindow.h"

class MyApplication: public Application
{
public:
    MyApplication(){}
    virtual void StartApp(void *pApp);
};

#endif

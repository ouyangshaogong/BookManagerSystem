#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "common.h"
#include "proxy.h"

struct NotifyController
{
    string strClassName;
};



class Controller
{

public:
    virtual void handleEvent(NotifyController notify) = 0;

};

#endif //__CONTROLLER__
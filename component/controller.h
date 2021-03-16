#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "component.h"

class Controller
{

public:
    virtual void handleEvent(NotifyMsg notify) = 0;

};

#endif //__CONTROLLER__
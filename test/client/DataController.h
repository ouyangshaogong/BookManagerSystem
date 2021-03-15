#ifndef __DATA_CONTROLLER__
#define __DATA_CONTROLLER__

#include "controller.h"

class DataController: Controller
{

public:
    virtual void handleEvent(NotifyController notify);
};

#endif
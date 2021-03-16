#ifndef __DATA_CONTROLLER__
#define __DATA_CONTROLLER__

#include "controller.h"

class DataController: public Controller
{

public:
    virtual void handleEvent(NotifyMsg notify);
};

#endif

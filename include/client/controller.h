#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "common.h"

struct NotifyController
{

};

class Controller;

void RegisterCommand(int nCmdMsg, Controller *control);
void SendNotifyCation(int nCmdMsg);

class Controller
{

public:
    virtual void handleEvent(NotifyController notify);

};

#endif //__CONTROLLER__
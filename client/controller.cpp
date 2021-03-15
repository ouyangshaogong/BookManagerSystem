#include "controller.h"

map<int, Controller*> g_nMsgMapController;
NotifyController g_notifyControl;

void RegisterCommand(int nCmdMsg, Controller *control)
{
    g_nMsgMapController.insert(map<int, Controller*>::value_type(nCmdMsg, control));
}

void SendNotifyCation(int nCmdMsg)
{
    map<int, Controller*>::iterator iter = g_nMsgMapController.find(nCmdMsg);
    if (iter != g_nMsgMapController.end())
    {
        iter->second->handleEvent(g_notifyControl);
    }
    
}

void Controller::handleEvent(NotifyController notify)
{
    // execute addlevel function
}
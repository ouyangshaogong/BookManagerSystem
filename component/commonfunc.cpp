#include "commonfunc.h"

map<int, void*> g_nMsgMapController;
NotifyController g_notifyControl;

View *g_nView;
NotifyView g_nNotifyView;

Proxy *g_nProxy;
map<string, void*> g_StringMapProxy;

void RegisterCommand(int nCmdMsg, void *control)
{
    g_nMsgMapController.insert(map<int, void*>::value_type(nCmdMsg, control));
}

void SendNotifyCationToController(int nCmdMsg)
{
    map<int, void*>::iterator iter = g_nMsgMapController.find(nCmdMsg);
    if (iter != g_nMsgMapController.end())
    {
        Controller *control = (Controller*)iter->second;
        g_notifyControl.strClassName = g_nProxy->GetProxyName();
        control->handleEvent(g_notifyControl);
    }
    
}


void RegisterProxy(void *proxy)
{
    g_nProxy = (Proxy*)proxy;
    g_StringMapProxy.insert(map<string, void*>::value_type(g_nProxy->GetProxyName(), proxy));
}

void* RetrieveProxy(string strName)
{
    map<string, void*>::iterator iter = g_StringMapProxy.find(strName);
    if (iter != g_StringMapProxy.end())
    {
        return iter->second;
    }

    return NULL;
}


void RegisterView(View *view)
{
    g_nView = view;
}
//send data to view
void SendNotifyCationToView(int nMsg, void *pCommonData)
{
    list<int> listMsg = g_nView->ReceiveMsg();

    list<int>::iterator iter = listMsg.begin();
    for (; iter != listMsg.end(); ++iter)
    {
        if ((*iter) == nMsg)
        {
            g_nNotifyView.nMsg = nMsg;
            g_nNotifyView.pCommonData = pCommonData;
            g_nView->HandleNotifyCation(g_nNotifyView);
            break;
        }
    }
    
}
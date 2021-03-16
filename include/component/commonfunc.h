#ifndef __COMMON_FUNC__
#define __COMMON_FUNC__

#include "controller.h"
#include "view.h"
#include "proxy.h"

void RegisterCommand(int nCmdMsg, void *control);
void SendNotifyCationToController(int nCmdMsg);


void RegisterProxy(void *proxy);
void* RetrieveProxy(string strName);

void RegisterView(View *view);
void SendNotifyCationToView(int nMsg, void *pCommonData);



#endif 
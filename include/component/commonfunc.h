#ifndef __COMMON_FUNC__
#define __COMMON_FUNC__

#include "controller.h"
#include "view.h"
#include "proxy.h"

class CommonFunc
{
public:
    static CommonFunc* Instance();
    void DestoryInstance();

    virtual void RegisterCommand(int nCmdMsg, void *control);
    virtual void SendNotifyCationToController(int nCmdMsg);


    virtual void RegisterProxy(void *proxy);
    virtual void* RetrieveProxy(string strName);

    virtual void RegisterView(View *view);
    virtual void SendNotifyCationToView(int nMsg, void *pCommonData);
    NotifyView GetNotifyView();

private:
    CommonFunc(){}

private:
    map<int, void*> m_nMsgMapController;
    NotifyController m_notifyControl;

    View *m_nView;
    NotifyView m_nNotifyView;

    Proxy *m_nProxy;
    map<string, void*> m_StringMapProxy;

    static CommonFunc* m_instance;
    static pthread_mutex_t m_Mutex;
};

#endif 

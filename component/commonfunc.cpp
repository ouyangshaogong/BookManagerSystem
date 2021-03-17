#include "commonfunc.h"

pthread_mutex_t CommonFunc::m_Mutex = PTHREAD_MUTEX_INITIALIZER;
CommonFunc* CommonFunc::m_instance = NULL;

CommonFunc* CommonFunc::Instance()
{
    if (m_instance == NULL)
    {
        pthread_mutex_lock(&m_Mutex);    // 加锁

        if (m_instance == NULL)
        {
            m_instance = new CommonFunc();           
        }

        pthread_mutex_unlock(&m_Mutex);  // 解锁
    }

    return m_instance;
}

void CommonFunc::DestoryInstance()
{
    if (m_instance != NULL)
    {
        pthread_mutex_lock(&m_Mutex);    // 加锁

        if (m_instance != NULL)
        {
            delete m_instance;
		    m_instance = NULL;
        }

        pthread_mutex_unlock(&m_Mutex);  // 解锁
    }
    
}



void CommonFunc::RegisterCommand(int nCmdMsg, void *control)
{
    m_nMsgMapController.insert(map<int, void*>::value_type(nCmdMsg, control));
}

void CommonFunc::SendNotifyCationToController(int nCmdMsg, NotifyMsg notify)
{
    map<int, void*>::iterator iter = m_nMsgMapController.find(nCmdMsg);
    if (iter != m_nMsgMapController.end())
    {
        Controller *control = (Controller*)iter->second;
        notify.strClassName = m_nProxy->GetProxyName();
        control->handleEvent(notify);
    }
    
}


void CommonFunc::RegisterProxy(void *proxy)
{
    m_nProxy = (Proxy*)proxy;
    m_StringMapProxy.insert(map<string, void*>::value_type(m_nProxy->GetProxyName(), proxy));
}

void* CommonFunc::RetrieveProxy(string strName)
{
    map<string, void*>::iterator iter = m_StringMapProxy.find(strName);
    if (iter != m_StringMapProxy.end())
    {
        return iter->second;
    }

    return NULL;
}


void CommonFunc::RegisterView(View *view)
{
    m_nView = view;
}
//send data to view
void CommonFunc::SendNotifyCationToView(NotifyMsg notify)
{
    list<int> listMsg = m_nView->ReceiveMsg();

    list<int>::iterator iter = listMsg.begin();
    for (; iter != listMsg.end(); ++iter)
    {
        if ((*iter) == notify.nMsg)
        {
            m_nView->HandleNotifyCation(notify);
            break;
        }
    }
    
}
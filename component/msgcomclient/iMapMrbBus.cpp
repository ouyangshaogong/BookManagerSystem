#include "iMapMrbBus.h"
#include "MyMsgServer.h"

ACE_Thread_Mutex iMapMrbBus::m_mutex;
iMapMrbBus* iMapMrbBus::m_instance = NULL;
iMapMrbBus::iMapMrbBus(TaskMgrApp *pTaskMgrApp)
{
    m_pTaskMgrApp = pTaskMgrApp;
    m_pMsgServer = MyMsgServer::Instance(pTaskMgrApp);
}

iMapMrbBus::~iMapMrbBus()
{
    if (NULL != m_instance)
    {
        delete m_instance;
    }
}

iMapMrbBus* iMapMrbBus::Instance(TaskMgrApp *pTaskMgrApp)
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new iMapMrbBus(pTaskMgrApp);
        }
    }
    
    return m_instance;
}

int iMapMrbBus::open()
{
    activate();
    return 0;
}

int iMapMrbBus::svc()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMrbBus::svc>>\n"));
    m_pMsgServer->open();
    
    while(true)
    {
        ACE_Reactor::instance ()->handle_events();
    }
    
    return 0;
}

int iMapMrbBus::close()
{
    return 0;
}


void iMapMrbBus::StartBus()
{
    int nRet = m_pTaskMgrApp->InitProcessEnv(ACE_Thread_Manager::instance());
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskApp->InitProcessEnv fail!\n"));
    }

    //创建一个任务管理器
    TaskMgr* pTaskMgr = new TaskMgr;
    nRet = pTaskMgr->InitEnv(1, m_pTaskMgrApp->GetGlobalTaskMgrID());
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskMgr->InitEnv fail!\n"));
    }

    //连接服务器
    m_pMsgServer->open();
     //创建2个任务，用来响应消息
    MyMsgServerTask *pTaskStatic = new MyMsgServerTask(m_pMsgServer);
    pTaskStatic->InitEnv(3, pTaskMgr->GetGlobalTaskID());
    pTaskStatic->open();
    //将任务插入任务管理器
    pTaskMgr->InsertTask(pTaskStatic);

    /*MyMsgServerTask *pTaskDynamic = new MyMsgServerTask(m_pMsgServer);
    pTaskDynamic->InitEnv(1, pTaskMgr->GetGlobalTaskID());

    MrbMsgClient *mrbMsgClient = new MrbMsgClient;
    mrbMsgClient->SetMsgValue(50, pTaskMgr->GetLocalTaskMgrID(), pTaskDynamic->GetLocalTaskID());
    pTaskDynamic->CreateDynamicTask(mrbMsgClient);
    //pTaskStatic->SetMsgValue(50, pTaskMgr->GetLocalTaskMgrID());
    pTaskMgr->InsertTask(pTaskDynamic);*/

    //将任务管理器插入任务APP
    m_pTaskMgrApp->InsertTaskMgr(pTaskMgr);
}

void iMapMrbBus::StartMsgLoop()
{
    m_pMsgServer->StartMsgLoop();
}

void iMapMrbBus::StopBus()
{
    m_pTaskMgrApp->ExitThread();

    m_pTaskMgrApp->TaskMgrDestory();
}
#include "iMapMrbBus.h"
#include "iMapConnectorHandle.h"
#include "MsgClientTask.h"

ACE_Thread_Mutex iMapMrbBus::m_mutex;
iMapMrbBus* iMapMrbBus::m_instance = NULL;
iMapMrbBus::iMapMrbBus(TaskMgrApp *pTaskMgrApp)
{
    m_pTaskMgrApp = pTaskMgrApp;
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


void iMapMrbBus::StartBus()
{
    int nRet = m_pTaskMgrApp->InitProcessEnv(ACE_Thread_Manager::instance());
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskApp->InitProcessEnv fail!\n"));
    }

    TaskMgr* pTaskMgr = new TaskMgr();
    nRet = pTaskMgr->InitEnv(1, m_pTaskMgrApp->GetGlobalTaskMgrID());
    if (0 != nRet)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)::main>>pTaskMgr->InitEnv fail!\n"));
    }

    Task *pTaskStatic = new MsgClientTask;
    pTaskStatic->CreateStaticTask();
    pTaskStatic->InitEnv(3, pTaskMgr->GetGlobalTaskID());
    pTaskMgr->InsertTask(pTaskStatic);

    Task *pTaskDynamic = new MsgClientTask;
    pTaskDynamic->CreateDynamicTask();
    pTaskDynamic->InitEnv(3, pTaskMgr->GetGlobalTaskID());
    pTaskMgr->InsertTask(pTaskDynamic);

    m_pTaskMgrApp->InsertTaskMgr(pTaskMgr);
}

void iMapMrbBus::StartMsgLoop()
{
    m_pTaskMgrApp->StartMsgLoop();
}

void iMapMrbBus::StopBus()
{
    m_pTaskMgrApp->ExitThread();

    m_pTaskMgrApp->TaskMgrDestory();
}
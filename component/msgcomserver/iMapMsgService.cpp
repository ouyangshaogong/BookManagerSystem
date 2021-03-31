#include "iMapMsgService.h"

ACE_Thread_Mutex iMapMsgService::m_mutex;
iMapMsgService *iMapMsgService::m_instance = NULL;

iMapMsgService::iMapMsgService()
{

}

iMapMsgService::~iMapMsgService()
{
    if (NULL != m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL != m_instance)
        {
            delete m_instance;
        }
    }
}

iMapMsgService* iMapMsgService::Instance()
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new iMapMsgService();
        }
    }
    return m_instance;
}

int iMapMsgService::open()
{
    ACE_INET_Addr addr(5000, "127.0.0.1");

    if (m_acceptor.open(addr, ACE_Reactor::instance(), ACE_NONBLOCK) == -1)
    {
        return 1;
    }
    
    activate();
    return 0;
}

int iMapMsgService::close()
{
    return 0;
}

int iMapMsgService::svc()
{
    ACE_Reactor::instance()->run_reactor_event_loop();
    return 0;
}

void iMapMsgService::StartMsgLoop()
{
    m_acceptor.StartMsgLoop();
}
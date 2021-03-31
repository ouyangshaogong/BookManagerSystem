#ifndef __MAP_MSG_SERVICE__
#define __MAP_MSG_SERVICE__

#include "commonace.h"
#include "MyProtoMsg.h"
#include "iMapMsgHandle.h"
#include "ace/Thread.h"
#include "ace/Thread_Manager.h"
#include "ace/Thread_Mutex.h"
#include "ace/Log_Msg.h"
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "ace/Synch.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Connector.h"
#include "ace/Connector.h"
#include "ace/Svc_Handler.h"
#include "ace/Condition_T.h"
#include "ace/Log_Msg.h"
#include "ace/OS.h"
#include "ace/Task.h"
#include "ace/OS_NS_time.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Thread_Manager.h"

class iMapMsgService: public ACE_Task<ACE_MT_SYNCH>
{
public:

     static iMapMsgService* Instance();

    ~iMapMsgService();
    
    virtual int open();
    virtual int close();
    virtual int svc();

private:
    iMapMsgService();

private:
    iMapMsgAcceptor m_acceptor;
    static ACE_Thread_Mutex m_mutex;
    static iMapMsgService *m_instance;
    ACE_INET_Addr m_nInetAddr;
};

#endif
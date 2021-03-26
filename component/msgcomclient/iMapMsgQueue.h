#ifndef __MAP_MSG_QUEUE__
#define __MAP_MSG_QUEUE__

#include "ace/Thread.h"
#include "ace/Message_Queue.h"
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
#include "ace/Thread.h"
#include "ace/Message_Queue.h"
#include "ace/Thread_Manager.h"
#include "ace/Thread_Mutex.h"
#include "ace/Log_Msg.h"

class iMapMsgQueue: public ACE_Message_Queue<ACE_NULL_SYNCH>
{
public:
    iMapMsgQueue();
    virtual ~iMapMsgQueue();
};


#endif


#ifndef __MAP_MSG_HANDLE__
#define __MAP_MSG_HANDLE__

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

#include "iMapCmdMsg.h"
#include <list>

using namespace std;

class iMapMsgHandle: public ACE_Event_Handler
{
   
public:
    static iMapMsgHandle *Instance();
    virtual ~iMapMsgHandle();

    virtual int open(void * = 0);

    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_timeout(const ACE_Time_Value &current_time, const void *act = 0);

    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    ACE_HANDLE get_handle() const;

    ACE_SOCK_Stream& Peer();

    void StartMsgLoop();

    void SendExternalCmdMsg(iMapCmdMsg *pCmdMsg);

    void SendInternalCmdMsg(iMapCmdMsg *pCmdMsg);

    void RecvExternalCmdMsg(iMapCmdMsg *pCmdMsg);

    void RecvInternalCmdMsg(iMapCmdMsg *pCmdMsg);

private:
    iMapMsgHandle(); 

private:
    ACE_SOCK_Stream m_socketPeer;

private:
    static iMapMsgHandle *m_instance;
    static ACE_Thread_Mutex m_mutex;
    list<iMapCmdMsg*> m_iMapCmdMsg;

    ACE_Thread_Mutex m_MsgMutex;
    ACE_Condition<ACE_Thread_Mutex> m_MsgCond;
};

#endif // __MAP_MSG_HANDLE__

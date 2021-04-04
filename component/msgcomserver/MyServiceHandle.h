#ifndef __MAP_MSG_HANDLE__
#define __MAP_MSG_HANDLE__

#include <ace/OS.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Auto_Ptr.h>
#include "ace/Acceptor.h"
#include "ace/Log_Msg.h"
#include "ace/Thread.h"
#include "ace/Task.h"
#include "ace/Thread_Manager.h"
#include "ace/Thread_Mutex.h"

#include "commonace.h"
#include "MyProtoMsg.h"
#include "MyMsgQueue.h"
#include "MyMsgServer.h"

class MyServiceHandle : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
public:

    MyServiceHandle();
    virtual ~MyServiceHandle();

    int open(void *p);

    virtual int handle_input(ACE_HANDLE fd);

    virtual int handle_output(ACE_HANDLE fd);

    // 释放相应资源
    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);

private:
    static MyMsgServer *m_pMsgServer;

    ACE_TCHAR m_peerName[512];
    ACE_INET_Addr m_peerAddr;
     
};

typedef ACE_Acceptor<MyServiceHandle, ACE_SOCK_ACCEPTOR> iMapMsgAcceptor;


#endif

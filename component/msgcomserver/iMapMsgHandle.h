#ifndef __MAP_MSG_HANDLE__
#define __MAP_MSG_HANDLE__

#include <ace/OS.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Auto_Ptr.h>
#include "ace/Acceptor.h"
#include "ace/Log_Msg.h"
#include "commonace.h"
#include "MyProtoMsg.h"
#include "MyMsgQueue.h"
#include "ace/Thread.h"
#include "ace/Task.h"
#include "ace/Thread_Manager.h"
#include "ace/Thread_Mutex.h"


//nCmdMsg
const int CMD_MSG_SERVICE_REGISTER = 1;

//nMsgType
#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300


class iMapMsgHandle : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
public:

    iMapMsgHandle();
    virtual ~iMapMsgHandle();

    int open(void *p);

    virtual int handle_input(ACE_HANDLE fd);

    virtual int handle_output(ACE_HANDLE fd);

    // 释放相应资源
    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);

    int SendCmdMsgToQueue(MyProtoMsg *pMsg);

    int SendCmdMsgToProc(MyProtoMsg *pMsg, int nProcID);

private:
    static ACE_Thread_Mutex m_mapMutex;
    static map<int, ACE_SOCK_Stream> m_nProcMapSocket;
    MyMsgQueue m_mMsgQueue;
     
};

typedef ACE_Acceptor<iMapMsgHandle, ACE_SOCK_ACCEPTOR> iMapMsgAcceptor;

#endif

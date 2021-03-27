#ifndef __MAP_MSG_SERVICE__
#define __MAP_MSG_SERVICE__

#include <ace/OS.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Auto_Ptr.h>
#include "ace/Log_Msg.h"
#include "commonace.h"
#include "iMapCmdMsg.h"

const int CMD_MSG_SERVICE_REGISTER = 1;

class iMapMsgService : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
public:

    iMapMsgService();
    virtual ~iMapMsgService();

    int open(void *p);

    virtual int handle_input(ACE_HANDLE fd);

    virtual int handle_output(ACE_HANDLE fd);

    // 释放相应资源
    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);

    int SendCmdMsgToQueue(iMapCmdMsg *pCmdMsg);

    int SendCmdMsgToProc(iMapCmdMsg *pCmdMsg);

private:
    ACE_SOCK_Stream m_sockStream;
    bool m_bRunning;

    static ACE_Thread_Mutex m_mapMutex;
    static map<int, ACE_SOCK_Stream> m_nProcMapSocket;
};

typedef ACE_Acceptor<iMapMsgService, ACE_SOCK_ACCEPTOR> iMapMsgAcceptor;

#endif

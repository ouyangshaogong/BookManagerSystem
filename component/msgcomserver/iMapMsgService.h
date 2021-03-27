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

class iMapMsgService : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
public:
    ACE_SOCK_Stream &peer(void);

    int open(void*);

    int close(u_long);

    int svc(void);

    virtual ACE_HANDLE get_handle(void) const;

    virtual int handle_input(ACE_HANDLE fd);

    // 释放相应资源
    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);

protected:
    
    ACE_SOCK_Stream m_sockStream;
};

typedef ACE_Acceptor<iMapMsgService, ACE_SOCK_ACCEPTOR> iMapMsgAcceptor;

#endif

#ifndef __MSG_SERVICE_HANDLE__
#define __MSG_SERVICE_HANDLE__

#include "MyMsgServer.h"
#include "commonace.h"
#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"

class MsgServiceHandle: public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
public:
    MsgServiceHandle();
    virtual ~MsgServiceHandle();

    virtual int open(void *p);

    virtual int handle_input(ACE_HANDLE fd);

    virtual int handle_output(ACE_HANDLE fd);

    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);
    
private:
    static MyMsgServer *m_pMsgServer;
    ACE_TCHAR m_peerName[512];
    ACE_INET_Addr m_peerAddr;
};

typedef ACE_Acceptor<MsgServiceHandle, ACE_SOCK_ACCEPTOR> MsgServiceAcceptor;

#endif
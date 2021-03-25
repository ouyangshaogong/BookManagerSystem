#ifndef __MAP_ACCEPT_HANDLE__
#define __MAP_ACCEPT_HANDLE__

#include "iMapMsgHandle.h"
#include "ace/Reactor.h"
#include "ace/SOCK_Acceptor.h"


class iMapAcceptHandle: public ACE_Event_Handler
{
public:
    iMapAcceptHandle(iMapMsgHandle *pMsgHandle);

    int open(ACE_Addr &addr);

    int handle_input(ACE_HANDLE handle);

    ACE_HANDLE GetHandle(void) const;

private:
    ACE_SOCK_Acceptor m_peerAcceptor;
    iMapMsgHandle *m_pMsgHandle;
    ACE_Reactor *m_pReactor;
};

#endif

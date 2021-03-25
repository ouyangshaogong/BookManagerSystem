#include "iMapAcceptHandle.h"

iMapAcceptHandle::iMapAcceptHandle(iMapMsgHandle *pMsgHandle)
{
    m_pMsgHandle = pMsgHandle;
}

int iMapAcceptHandle::open(ACE_Addr &addr)
{
    m_pMsgHandle->open();
    m_peerAcceptor.open(addr);
    return 0;
}

int iMapAcceptHandle::handle_input(ACE_HANDLE handle)
{
    if (this->m_peerAcceptor.accept(m_pMsgHandle->Peer(), 0, 0, 1) == -1)
    {
        ACE_DEBUG((LM_ERROR, "Error in connection\n"));
    }

    ACE_DEBUG((LM_DEBUG, "Connection established\n"));
    
    return -1;
}

ACE_HANDLE iMapAcceptHandle::GetHandle(void) const
{
    return this->m_peerAcceptor.get_handle();
}
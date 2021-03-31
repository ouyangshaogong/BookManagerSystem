#ifndef __MAP_CONNECTOR_HANDLE__
#define __MAP_CONNECTOR_HANDLE__

#include "commonace.h"
#include "MyProtoMsg.h"

using namespace std;

class iMapConnectorHandle: public ACE_Event_Handler
{
public:
    iMapConnectorHandle();
    ~iMapConnectorHandle();

    virtual int open();

    virtual int handle_input(ACE_HANDLE fd);

    virtual int handle_timeout(const ACE_Time_Value &current_time, const void *act = 0);

    //virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask);

    ACE_HANDLE get_handle(void) const;

    void SendCmdMsgToServer(MyProtoMsg *pMsg);

private:
    ACE_SOCK_Connector m_connector;
    ACE_SOCK_Stream m_socketPeer;

    int m_nMsgID;
};


#endif




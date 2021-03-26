#ifndef __MAP_MSG_HANDLE__
#define __MAP_MSG_HANDLE__

#include "commonace.h"
#include "iMapCmdMsg.h"
#include "iMapMsgQueue.h"
#include "iMapConnectorHandle.h"

using namespace std;

class iMapMsgHandle: public ACE_Task<ACE_MT_SYNCH>
{
   
public:
    static iMapMsgHandle *Instance();
    virtual ~iMapMsgHandle();

    virtual int open();

    int close(u_long);

    int svc(void);

    void SendInternalCmdMsg(iMapCmdMsg *pCmdMsg);

    void SendExternalCmdMsg(iMapCmdMsg *pCmdMsg);

     ACE_THR_FUNC_RETURN StartMsgLoop();

private:
    iMapMsgHandle();

private:
    static iMapMsgHandle *m_instance;
    static ACE_Thread_Mutex m_mutex;
    iMapConnectorHandle m_connectorHandle;
    bool m_bRunning;
};

#endif // __MAP_MSG_HANDLE__

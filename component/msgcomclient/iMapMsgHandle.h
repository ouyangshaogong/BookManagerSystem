#ifndef __MAP_MSG_HANDLE__
#define __MAP_MSG_HANDLE__

#include "commonace.h"
#include "iMapCmdMsg.h"
#include "iMapConnectorHandle.h"

using namespace std;

class iMapMsgHandle: public ACE_Task<ACE_MT_SYNCH>
{
   
public:
    static iMapMsgHandle *Instance();
    virtual ~iMapMsgHandle();

    virtual int open(iMapConnectorHandle *pConnectorHandle);

    int close(u_long);

    int svc(void);

    void SendCmdMsgToQueue(iMapCmdMsg *pCmdMsg);

    void SendCmdMsgToServer(iMapCmdMsg *pCmdMsg);

    virtual void process(iMapCmdMsg *pInCmdMsg, iMapCmdMsg *pOutCmdMsg);

private:
    iMapMsgHandle();

private:
    static iMapMsgHandle *m_instance;
    static ACE_Thread_Mutex m_mutex;
    iMapConnectorHandle *m_pConnectorHandle;

    ACE_Thread_Mutex m_mqMutex;
    bool m_bRunning;
};

#endif // __MAP_MSG_HANDLE__

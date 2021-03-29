#ifndef __MAP_MSG_HANDLE__
#define __MAP_MSG_HANDLE__

#include "commonace.h"
#include "MyProtoMsg.h"
#include "iMapConnectorHandle.h"

using namespace std;

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

const int CMD_MSG_SERVICE_REGISTER = 1;

const int SEND_PROC_ID = 51;
const int RECV_PROC_ID = 50;

class iMapMsgHandle: public ACE_Task<ACE_MT_SYNCH>
{
   
public:
    static iMapMsgHandle *Instance();
    virtual ~iMapMsgHandle();

    virtual int open(iMapConnectorHandle *pConnectorHandle);

    int close(u_long);

    int svc(void);

    void SendCmdMsgToQueue(uint8_t* pData, int nLength);

    void SendCmdMsgToServer(uint8_t* pData, int nLength);
    void SendCmdMsgToServer(MyProtoMsg *pMsg);

    virtual void process(MyProtoMsg *pInMsg, MyProtoMsg *pOutMsg);

private:
    iMapMsgHandle();

private:
    static iMapMsgHandle *m_instance;
    static ACE_Thread_Mutex m_mutex;
    iMapConnectorHandle *m_pConnectorHandle;

    ACE_Thread_Mutex m_mqMutex;
    bool m_bRunning;

    MyProtoDecode m_protoDecode;
    MyProtoEncode m_protoEncode;
};

#endif // __MAP_MSG_HANDLE__

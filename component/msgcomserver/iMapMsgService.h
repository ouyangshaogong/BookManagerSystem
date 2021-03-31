#ifndef __MAP_MSG_LOOP__
#define __MAP_MSG_LOOP__

#include "commonace.h"
#include "MyProtoMsg.h"
#include "iMapMsgHandle.h"

class iMapMsgService: public ACE_Task<ACE_MT_SYNC>
{
public:

     static iMapMsgService* Instance();

    ~iMapMsgService();
    
    void StartMsgLoop();
    
    virtual int open();
    virtual int close();
    virtual int svc();

private:
    iMapMsgService();

private:
    iMapMsgHandle m_acceptor;
    static ACE_Thread_Mutex m_mutex;
    static iMapMsgService *m_instance;
};

#endif
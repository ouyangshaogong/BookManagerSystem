#ifndef __MAP_CONNECTOR_HANDLE__
#define __MAP_CONNECTOR_HANDLE__

#include "commonace.h"
#include "MyProtoMsg.h"
#include "TaskMgrApp.h"

using namespace std;

class iMapConnectorHandle: public ACE_Event_Handler
{
public:
    iMapConnectorHandle(TaskMgrApp *pTaskMgrApp, int nSendProc, int nTaskMgrID, TaskID nTaskID);
    ~iMapConnectorHandle();

    virtual int open();

    virtual int handle_input(ACE_HANDLE fd);

    virtual int handle_timeout(const ACE_Time_Value &current_time, const void *act = 0);

    //virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask);

    ACE_HANDLE get_handle(void) const;

    void SendCmdMsgToTask(MyProtoMsg* pMsg);

    void SendCmdMsgToServer(uint8_t* pData, int nLength);

    void CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result);
    Json::Value& CallMethod(int nCmdMsg, const Json::Value &parameter);

private:
    ACE_SOCK_Connector m_connector;
    ACE_SOCK_Stream m_socketPeer;

    TaskMgrApp *m_pTaskMgrApp;

    MyProtoDecode m_protoDecode;
    MyProtoEncode m_protoEncode;
    MyProtoMsg m_protoMsg;
    int m_nMsgID;
};


#endif




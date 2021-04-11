#ifndef __MRB_MSG_CLIENT__
#define __MRB_MSG_CLIENT__

#include "MyProtoMsg.h"
#include "commonace.h"
#include "MyMsgServer.h"
#include "MyClientHandle.h"

#define SERVER 5001

const int CMD_MSG_SERVICE_REGISTER = 1;

const int SEND_PROC_ID = 51;
const int RECV_PROC_ID = 50;


class MyMsgClient
{
public:
    MyMsgClient();
    ~MyMsgClient();

    void SetMsgValue(int nSendProc, int nTaskMgrID, int nTaskID);

    int CallMethod(int nCmdCode, const Json::Value &InParam, Json::Value& OutParam);
    Json::Value& CallMethod(int nCmdCode, const Json::Value &parameter);

private:
    int m_nMsgID;
    MyProtoMsg m_protoMsg;
    MyClientHandle m_sockHandle;
    MyMsgServer *m_pMsgServer;

    string m_strIP;
    int m_nPort;
};

#endif

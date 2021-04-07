#ifndef __MRB_MSG_CLIENT__
#define __MRB_MSG_CLIENT__

#include "MyProtoMsg.h"
#include "commonace.h"
#include "MyMsgServer.h"
#include "MyClientHandle.h"

class MyMsgClient
{
public:
    MyMsgClient();
    ~MyMsgClient();

    void SetMsgValue(int nSendProc, int nTaskMgrID, int nTaskID);

    int CallMethod(int nCmdCode, const Json::Value &parameter, Json::Value& result);
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

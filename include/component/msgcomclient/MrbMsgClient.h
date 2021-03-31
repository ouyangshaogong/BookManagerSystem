#ifndef __CMD_MSG_CLIENT__
#define __CMD_MSG_CLIENT__

#include "MyProtoMsg.h"
#include "MsgClientTaskMgrApp.h"

class MrbMsgClient
{
public:
    MrbMsgClient();
    ~MrbMsgClient();

    void SetMsgValue(int nSendProc, int nTaskMgrID, TaskID nTaskID);

    void CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result);
    Json::Value& CallMethod(int nCmdMsg, const Json::Value &parameter);

private:
    int m_nMsgID;
    MyProtoMsg m_protoMsg;
    MsgClientTaskMgrApp *m_pClientTaskMgrApp;
};

#endif

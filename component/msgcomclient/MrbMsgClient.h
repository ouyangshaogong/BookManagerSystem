#ifndef __MRB_MSG_CLIENT__
#define __MRB_MSG_CLIENT__

#include "MyProtoMsg.h"

class MrbMsgClient
{
public:
    MrbMsgClient();
    ~MrbMsgClient();

    void SetMsgValue(int nSendProc, int nTaskMgrID, int nTaskID);

    void CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result);
    Json::Value& CallMethod(int nCmdMsg, const Json::Value &parameter);

private:
    int m_nMsgID;
    MyProtoMsg m_protoMsg;
};

#endif

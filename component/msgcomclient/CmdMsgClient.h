#ifndef __CMD_MSG_CLIENT__
#define __CMD_MSG_CLIENT__

#include "TaskMgrApp.h"
#include "iMapConnectorHandle.h"

class CmdMsgClient
{
public:
    CmdMsgClient();
    ~CmdMsgClient();

    void SendCmdMsgToTask(MyProtoMsg* pMsg);

    void CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result);
    Json::Value& CallMethod(int nCmdMsg, const Json::Value &parameter);

private:
    TaskMgrApp *m_pTaskMgrApp;
    iMapConnectorHandle *m_pConnecotorHandle;
};

#endif

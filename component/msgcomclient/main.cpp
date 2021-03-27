#include "iMapMsgHandle.h"
#include "ace/OS.h"
#include "ace/ACE.h"
#include "ace/Init_ACE.h"

using namespace std;

ACE_THR_FUNC_RETURN Work(void *arg)
{
    ACE_OS::sleep(3);
    iMapMsgHandle *pCmdHandle = (iMapMsgHandle*)arg;
    for (int i = 0; i < 10; i++)
    {
        iMapCmdMsg *pCmdMsg = new iMapCmdMsg;
        
        pCmdMsg->SetMsgID(i + 1);
        pCmdMsg->SetMsgType(REQUEST_MSG_TYPE);

        string str("test");
        pCmdMsg->SetBody(str);
        pCmdMsg->SetMsgLength(sizeof(iMapCmdMsg) + pCmdMsg->GetBody().length());
        ACE_DEBUG((LM_DEBUG, "(%P|%t)Work>>sizeof(iMapCmdMsg):%d\n", sizeof(iMapCmdMsg)));
        pCmdHandle->SendCmdMsgToQueue(pCmdMsg);
        ACE_OS::sleep(1);
    }
}



int ACE_TMAIN(int argc, char* argv[])
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t|)Message Communicate Client.......\n"));

    
    iMapMsgHandle *pCmdHandle = iMapMsgHandle::Instance();
    iMapConnectorHandle m_connectorHandle(pCmdHandle);

    m_connectorHandle.open();
    pCmdHandle->open(&m_connectorHandle);

    //创建消息循环线程,启动一个消息通信客户端消息循环
    ACE_Thread_Manager::instance()->spawn_n(1, Work, pCmdHandle);

    while (true)
    {
        ACE_Reactor::instance()->handle_events();
    }

    //等待线程退出
    ACE_Thread_Manager::instance()->wait();
    return 0;
}

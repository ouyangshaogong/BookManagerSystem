#include <sys/types.h>
#include "iMapMsgHandle.h"
#include "ace/OS.h"
#include <iostream>
#include "ace/Thread_Manager.h"

ACE_THR_FUNC_RETURN Work(void *arg)
{
    iMapMsgHandle *pCmdMsgHandle = (iMapMsgHandle*)arg;

    for (int i = 0; i < 10; ++i)
    {
        iMapCmdMsg *pCmdMsg = new iMapCmdMsg;
        pCmdMsg->SetMsgID(i + 1);
        pCmdMsg->SetMsgType(REQUEST_MSG_TYPE);
        pCmdMsg->SetBody("test");
        pCmdMsgHandle->RecvCmdMsg(pCmdMsg);
    }
    
}


using namespace std;


int ACE_TMAIN(int argc, char* argv[])
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t|)Message Communicate Client.......\n"));

    

    iMapMsgHandle *pCmdHandle = iMapMsgHandle::Instance();
    pCmdHandle->open();

    //创建测试线程
    ACE_Thread_Manager::instance()->spawn_n(1, Work, (void*)pCmdHandle);
    
    //启动一个消息通信客户端消息循环
    pCmdHandle->StartMsgLoop();

    
    // Listing 1
    ACE_Thread_Manager::instance()->wait();

    return 0;
}

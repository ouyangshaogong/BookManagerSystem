#include <sys/types.h>
#include "iMapMsgHandle.h"
#include "ace/OS.h"
#include <iostream>

#include "iMapMsgQueue.h"
#include "ace/ACE.h"
#include "ace/Init_ACE.h"


using namespace std;

ACE_THR_FUNC_RETURN StartMsgLoop(void *arg)
{
    iMapMsgHandle *pCmdHandle = (iMapMsgHandle*)arg;
    pCmdHandle->StartMsgLoop();
}

ACE_Thread_Mutex g_mqMutex;
iMapMsgQueue g_MQ;

int ACE_TMAIN(int argc, char* argv[])
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t|)Message Communicate Client.......\n"));
    ACE::init();

    g_MQ.high_water_mark(10 * 1024 * 1024);
    g_MQ.low_water_mark(2 * 1024 * 1024);
    g_MQ.activate();

    iMapMsgHandle *pCmdHandle = iMapMsgHandle::Instance();
    pCmdHandle->open();

    //创建消息循环线程,启动一个消息通信客户端消息循环
    ACE_Thread_Manager::instance()->spawn_n(1, StartMsgLoop, (void*)0);

    while (true)
    {
        ACE_Reactor::instance()->handle_events();
    }
        

    //等待线程退出
    ACE_Thread_Manager::instance()->wait();

    ACE::fini();
    return 0;
}

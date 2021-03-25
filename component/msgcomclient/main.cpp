#include <sys/types.h>
#include "iMapMsgHandle.h"
#include <iostream>

using namespace std;



int ACE_TMAIN(int argc, char* argv[])
{
    ACE_DEBUG((LM_DEBUG, "Message Communicate Client.......\n"));

    iMapMsgHandle *pCmdHandle = iMapMsgHandle::Instance();
    pCmdHandle->open();
    
    //启动一个消息通信客户端消息循环
    pCmdHandle->StartMsgLoop();

    return 0;
}

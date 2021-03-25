
#include <sys/types.h>
#include "iMapMsgHandle.h"
#include "iMapAcceptHandle.h"

#include <iostream>

using namespace std;

#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

int ACE_TMAIN(int argc, char* argv[])
{
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("Message Communicate Client.......\n")));

    ACE_INET_Addr addr(PORT_NO, HOSTNAME);
    iMapMsgHandle *pCmdHandle = iMapMsgHandle::Instance();
    iMapAcceptHandle *pAcceptHandle = new iMapAcceptHandle(pCmdHandle);

    pAcceptHandle->open(addr);
    ACE_Reactor::instance()->register_handler(pAcceptHandle, ACE_Event_Handler::ACCEPT_MASK);
    //启动一个消息通信客户端消息循环
    pCmdHandle->StartMsgLoop();

    return 0;
}

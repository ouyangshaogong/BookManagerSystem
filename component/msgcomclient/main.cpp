#include <sys/types.h>
#include "iMapMsgHandle.h"
#include <iostream>

using namespace std;



int ACE_TMAIN(int argc, char* argv[])
{
    ACE_DEBUG((LM_DEBUG, "Message Communicate Client.......\n"));

    iMapMsgHandle *pCmdHandle = iMapMsgHandle::Instance();
    pCmdHandle->open();
    
    //����һ����Ϣͨ�ſͻ�����Ϣѭ��
    pCmdHandle->StartMsgLoop();

    return 0;
}

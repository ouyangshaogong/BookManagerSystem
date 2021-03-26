#ifndef __MAP_MSG_BLOCK__
#define __MAP_MSG_BLOCK__

#include "ace/Message_Queue.h"
#include "ace/Thread_Manager.h"
#include "ace/Thread_Mutex.h"
#include "ace/Log_Msg.h"
#include "iMapCmdMsg.h"

class iMapMsgBlock: public ACE_Message_Block
{
public:
    iMapMsgBlock(iMapCmdMsg *pCmdMsg, int nLength);
    ~iMapMsgBlock();
};


#endif

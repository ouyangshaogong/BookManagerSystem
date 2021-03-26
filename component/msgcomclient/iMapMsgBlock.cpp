#include "iMapMsgBlock.h"


iMapMsgBlock::iMapMsgBlock(iMapCmdMsg *pCmdMsg, int nLength)
    :ACE_Message_Block((size_t)nLength, MB_DATA, 0, 0)
{
    if (NULL != pCmdMsg)
    {
        (void)this->copy((char*)pCmdMsg, nLength);
    }
}


iMapMsgBlock::~iMapMsgBlock()
{
}

#include "DataView.h"

#define CMD_MSG_DATA_COMMAND 100

void DataView::UserInputEvent()
{
    //send controller
    SendNotifyCation(CMD_MSG_DATA_COMMAND);
}

list<int> DataView::ReceiveMsg()
{
    list<int> listMsg;
    listMsg.push_back(MSG_ADDLEVEL);

    return listMsg;
}

void DataView::HandleNotifyCation(NotifyView notify)
{
    switch(notify.nCmd)
    {
        case MSG_ADDLEVEL:
            
            break;
        default:
            break;
    }
}
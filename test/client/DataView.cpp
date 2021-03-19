#include "DataView.h"

#define CMD_MSG_DATA_COMMAND 100

extern void SendNotifyCationToController(int nCmdMsg);

list<int> &DataView::ReceiveMsg()
{
    m_listMsg.push_back(MSG_ADDLEVEL);

    return m_listMsg;
}

void DataView::HandleNotifyCation(NotifyMsg notify)
{
    int *p = NULL;
    switch(notify.nMsg)
    {
        case MSG_ADDLEVEL:
            //p = (int*)notify.pCommonData;
            //cout << "AddLevel:" << *p << endl;
            break;
        default:
            break;
    }
}
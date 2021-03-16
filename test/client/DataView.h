#ifndef __DATA_VIEW__
#define __DATA_VIEW__

#include "view.h"

#define MSG_ADDLEVEL 1000
#define CMD_MSG_DATA_COMMAND 100

class DataView: public View
{
public:

    DataView(){}
    ~DataView(){}

    virtual list<int> ReceiveMsg();
    virtual void HandleNotifyCation(NotifyView notifydata);
};


#endif
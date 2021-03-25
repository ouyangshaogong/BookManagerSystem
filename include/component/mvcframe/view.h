#ifndef __VIEW__
#define __VIEW__

#include "component.h"

class View
{
public:

    virtual list<int>& ReceiveMsg() = 0;
    virtual void HandleNotifyCation(NotifyMsg notifydata) = 0;
protected:
    list<int> m_listMsg;
    //deal all other class send this class allowed receive msg

};

#endif
#ifndef __VIEW__
#define __VIEW__


#include "common.h"

using namespace std;

struct NotifyView
{
    int nMsg;
    void *pCommonData;
};

class View
{
public:

    virtual list<int> ReceiveMsg() = 0;
    virtual void HandleNotifyCation(NotifyView notifydata) = 0;

    //deal all other class send this class allowed receive msg

};

#endif
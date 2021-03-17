#ifndef __COMPONENT__
#define __COMPONENT__

#include "common.h"

struct NotifyMsg
{
public:
    int nMsg;
    string strClassName;
    map<string, void*> &GetMapParam();
private:
    map<string, void*> m_strMapVoid;
};



#endif
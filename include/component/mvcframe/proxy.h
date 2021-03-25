#ifndef __PROXY__
#define __PROXY__

#include "component.h"


class Proxy
{
public:
    Proxy();
    Proxy(string strName):m_strName(strName){};
    string GetProxyName();
private:
    string m_strName;
};

#endif //__PROXY__
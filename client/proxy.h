#ifndef __PROXY__
#define __PROXY__

#include "common.h"

class Proxy;

Proxy *g_Proxy;
void RegisterProxy(Proxy *proxy)
{
    g_Proxy = proxy;
}


class Proxy
{
public:
    Proxy(string strName):m_strName(strName){};
private:
    string m_strName;
};

#endif //__PROXY__
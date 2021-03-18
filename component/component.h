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

#define PACKAGEPARAMETER(className)\
void PackageParam##className(map<string, void*> &mapParam) \
{ \
} \
 \
template <class T, class ...Args> \
void PackageParam##className(map<string, void*> &mapParam, T head, Args... rest) \
{ \
    T *t = new T; \
    *t = head; \
    mapParam.insert(map<string, void*>::value_type(typeid(head).name(), (void*)t)); \
    PackageParam##className(mapParam, rest...); \
}

#define PARSEPARAMETER(className)\
void ParseParam##className(map<string, void*> &mapParam) \
{ \
    mapParam.clear(); \
} \
 \
template <class T, class ...Args> \
void ParseParam##className(map<string, void*> &mapParam, T &head, Args&... rest) \
{ \
    map<string, void*>::iterator iter = mapParam.find(typeid(T).name()); \
    if (iter != mapParam.end()) \
    { \
        head = *((T*)iter->second); \
    } \
 \
    T *t = (T*)iter->second; \
    delete t; \
 \
    ParseParam##className(mapParam, rest...); \
}

#endif
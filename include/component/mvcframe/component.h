#ifndef __COMPONENT__
#define __COMPONENT__

#include "common.h"

struct TypeValue
{
    string strType;
    void *nValue;
};

struct NotifyMsg
{
public:
    NotifyMsg():m_nIndex(0) {}
    int nMsg;
    string strClassName;
    void* pExtra;
    list<TypeValue> &GetMsgParam();
    int GetIndex();
private:
    list<TypeValue> m_strMapVoid;
    int m_nIndex;
};

#define PACKAGEPARAMETER(ClassName)\
void PackageParam##ClassName(NotifyMsg &notify) \
{ \
} \
 \
template <class T, class ...Args> \
void PackageParam##ClassName(NotifyMsg &notify, T head, Args... rest) \
{ \
    T *value = new T; \
    *value = head; \
    TypeValue typevalue; \
    typevalue.strType = typeid(T).name(); \
    typevalue.nValue = (void*)value; \
    notify.GetMsgParam().push_back(typevalue); \
    PackageParam##ClassName(notify, rest...); \
}

#define PARSEPARAMETER(ClassName)\
void ParseParam##ClassName(NotifyMsg &notify) \
{ \
    notify.GetMsgParam().clear(); \
} \
 \
template <class T, class ...Args> \
void ParseParam##ClassName(NotifyMsg &notify, T &head, Args&... rest) \
{ \
    int index = notify.GetIndex(); \
    if (index < notify.GetMsgParam().size()) \
    { \
        list<TypeValue>::iterator iter = notify.GetMsgParam().begin(); \
        int i = 0; \
        for (; i < index && iter != notify.GetMsgParam().end(); ++iter, ++i) {} \
        head = *((T*)iter->nValue); \
        T *t = (T*)iter->nValue; \
        delete t; \
    } \
 \
    ParseParam##ClassName(notify, rest...); \
}

#endif
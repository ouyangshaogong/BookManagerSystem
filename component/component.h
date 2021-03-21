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
    int nMsg;
    string strClassName;
    vector<TypeValue> &GetMsgParam();
private:
    vector<TypeValue> m_strMapVoid;
};

#define PACKAGEPARAMETER(className)\
void PackageParam##className(vector<TypeValue> &vecParam) \
{ \
} \
 \
template <class T, class ...Args> \
void PackageParam##className(vector<TypeValue> &vecParam, T head, Args... rest) \
{ \
    T *value = new T; \
    *value = head; \
    TypeValue typevalue; \
    typevalue.strType = typeid(T).name(); \
    typevalue.nValue = (void*)value; \
    vecParam.push_back(typevalue); \
    PackageParam##className(vecParam, rest...); \
}

#define PARSEPARAMETER(className)\
void ParseParam##className(vector<TypeValue> &vecParam) \
{ \
    vecParam.clear(); \
} \
 \
template <class T, class ...Args> \
void ParseParam##className(vector<TypeValue> &vecParam, T &head, Args&... rest) \
{ \
    vector<TypeValue>::iterator iter = vecParam.begin(); \
    for (; iter < vecParam.end();) \
    { \
        if ((*iter).strType == typeid(int).name()) \
        { \
            head = *((T*)(*iter).nValue); \
            T *value = (T*)iter->nValue; \
            delete value; \
        } \
    } \
 \
    ParseParam##className(vecParam, rest...); \
}

#endif
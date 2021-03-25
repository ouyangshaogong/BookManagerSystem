#include "component.h"

list<TypeValue> &NotifyMsg::GetMsgParam()
{
    return m_strMapVoid;
}

int NotifyMsg::GetIndex()
{
    return m_nIndex++;
}
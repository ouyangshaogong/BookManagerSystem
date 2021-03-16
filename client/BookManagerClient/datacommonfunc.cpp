#include "datacommonfunc.h"

void DataCommonFunc::RegisterView(Widget *widget)
{
    m_widgetView = widget;
}

void DataCommonFunc::SendNotifyCationToView(int nMsg, void *pCommonData)
{
    list<int> listMsg = m_widgetView->ReceiveMsg();

    list<int>::iterator iter = listMsg.begin();
    for (; iter != listMsg.end(); ++iter)
    {
        if ((*iter) == nMsg)
        {
            NotifyView notify = GetNotifyView();
            notify.nMsg = nMsg;
            notify.pCommonData = pCommonData;
            m_widgetView->HandleNotifyCation(notify);
            break;
        }
    }

}

#include "view.h"

View *g_view;
NotifyView g_NotifyView;

void RegisterView(View *view)
{
    g_view = view;
}
//send data to view
void SendNotifyCation(int nMsg, void *pCommonData)
{
    list<int> listMsg = g_view->ReceiveMsg();

    list<int>::iterator iter = listMsg.begin();
    for (; iter != listMsg.end(); ++iter)
    {
        if ((*iter) == nMsg)
        {
            g_view->HandleNotifyCation(g_NotifyView);
            break;
        }
    }
    
}
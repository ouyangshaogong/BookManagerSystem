#include "datacommonfunc.h"
#include <QDebug>

void DataCommonFunc::RegisterView(MainWindow *mainWin)
{
    m_mainWinView = mainWin;
}

void DataCommonFunc::SendNotifyCationToView(int nMsg, void *pCommonData)
{

    list<int> listMsg = m_mainWinView->ReceiveMsg();

    list<int>::iterator iter = listMsg.begin();
    for (; iter != listMsg.end(); ++iter)
    {
        if ((*iter) == nMsg)
        {
            qDebug() << "DataCommonFunc::SendNotifyCationToView>>" << nMsg;
            NotifyView notify = GetNotifyView();
            notify.nMsg = nMsg;
            notify.pCommonData = pCommonData;
            m_mainWinView->HandleNotifyCation(notify);
            break;
        }
    }

}

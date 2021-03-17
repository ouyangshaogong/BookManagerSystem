#include "datacommonfunc.h"
#include <QDebug>

void DataCommonFunc::RegisterView(MainWindow *mainWin)
{
    m_mainWinView = mainWin;
}

void DataCommonFunc::SendNotifyCationToView(NotifyMsg notify)
{
    list<int> listMsg = m_mainWinView->ReceiveMsg();

    list<int>::iterator iter = listMsg.begin();
    for (; iter != listMsg.end(); ++iter)
    {
        if ((*iter) == notify.nMsg)
        {
            qDebug() << "DataCommonFunc::SendNotifyCationToView>>" << notify.nMsg;
            m_mainWinView->HandleNotifyCation(notify);
            break;
        }
    }

}

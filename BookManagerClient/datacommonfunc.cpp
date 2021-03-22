#include "datacommonfunc.h"
#include <QDebug>

void DataCommonFunc::RegisterView(MainWindow *mainWin)
{
    m_mainWinView = mainWin;
    m_mainWinView->ReceiveMsg();
}

void DataCommonFunc::SendNotifyCationToView(NotifyMsg &notify)
{

    list<int>::iterator iter = m_mainWinView->ReceiveMsg().begin();
    for (; iter != m_mainWinView->ReceiveMsg().end(); ++iter)
    {
        if ((*iter) == notify.nMsg)
        {
            qDebug() << "DataCommonFunc::SendNotifyCationToView>>" << notify.nMsg;
            m_mainWinView->HandleNotifyCation(notify);
            break;
        }
    }

}

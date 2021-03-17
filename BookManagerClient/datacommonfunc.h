#ifndef DATACOMMONFUNC_H
#define DATACOMMONFUNC_H

#include "commonfunc.h"
#include "mainwindow.h"


class DataCommonFunc: public CommonFunc
{
public:

    virtual void SendNotifyCationToView(NotifyMsg notify);
    virtual void RegisterView(MainWindow *mainWin);
private:
    MainWindow *m_mainWinView;
};

#endif // DATACOMMONFUNC_H

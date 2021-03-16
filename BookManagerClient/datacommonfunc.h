#ifndef DATACOMMONFUNC_H
#define DATACOMMONFUNC_H

#include "commonfunc.h"
#include "mainwindow.h"


class DataCommonFunc: public CommonFunc
{
public:

    void SendNotifyCationToView(int nMsg, void *pCommonData);
    virtual void RegisterView(MainWindow *mainWin);
private:
    MainWindow *m_mainWinView;
};

#endif // DATACOMMONFUNC_H

#ifndef DATACOMMONFUNC_H
#define DATACOMMONFUNC_H

#include "commonfunc.h"
#include "widget.h"


class DataCommonFunc: public CommonFunc
{
public:

    void SendNotifyCationToView(int nMsg, void *pCommonData);
    virtual void RegisterView(Widget *widget);
private:
    Widget *m_widgetView;
};

#endif // DATACOMMONFUNC_H

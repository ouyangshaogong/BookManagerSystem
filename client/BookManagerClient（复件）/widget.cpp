#include "widget.h"
#include "ui_widget.h"
#include "commonfunc.h"
#include <QString>
#include <QDebug>

#define CMD_MSG_DATA_COMMAND 100

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


}



Widget::~Widget()
{
    delete ui;
}

list<int> Widget::ReceiveMsg()
{
    list<int> listMsg;
    listMsg.push_back(MSG_ADDLEVEL);

    return listMsg;
}

void Widget::HandleNotifyCation(NotifyView notify)
{
    int *p = NULL;
    switch(notify.nMsg)
    {
        case MSG_ADDLEVEL:
            p = (int*)notify.pCommonData;
            qDebug() << "LEVEL:" << QString().number(*p);
            break;
        default:
            break;
    }
}

void Widget::AddMenuBar()
{
    m_menuBar = menuBar();
    setMenuBar(m_menuBar);
}

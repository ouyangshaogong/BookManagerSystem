#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "view.h"
#include <QMenuBar>

#define MSG_ADDLEVEL 1000
#define CMD_MSG_DATA_COMMAND 100

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget, public View
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    virtual list<int> ReceiveMsg();
    virtual void HandleNotifyCation(NotifyView notifydata);

public:
    void AddMenuBar();

private:
    QMenuBar *m_menuBar;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

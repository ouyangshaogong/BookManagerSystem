#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = nullptr);

    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    void SendRightButton();
    void SendLeftButton();
};

#endif // MYLISTWIDGET_H

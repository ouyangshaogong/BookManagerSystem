#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QMouseEvent>
#include <QDebug>

class MyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyTableWidget(QWidget *parent = nullptr);

    void mouseReleaseEvent(QMouseEvent *ev);
signals:
    void SendRightButton();
};

#endif // MYTABLEWIDGET_H

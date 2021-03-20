#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent) : QListWidget(parent)
{

}

//鼠标释放
void MyListWidget::mouseReleaseEvent(QMouseEvent *ev)
{

    if(ev->button() == Qt::RightButton)
    {
        emit this->SendRightButton();
    }

    if(ev->button() == Qt::LeftButton)
    {
        emit this->SendLeftButton();
    }

}

#include "mytablewidget.h"

MyTableWidget::MyTableWidget(QWidget *parent) : QTableWidget(parent)
{

}


//鼠标释放
void MyTableWidget::mouseReleaseEvent(QMouseEvent *ev)
{

    if(ev->button() == Qt::RightButton)
    {
        emit this->SendRightButton();
    }

}

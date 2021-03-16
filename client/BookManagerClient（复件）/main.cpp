#include "widget.h"

#include <QApplication>
#include "MyApplication.h"
#include "datacommonfunc.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    MyApplication myApplication;
    myApplication.StartApp(&w);

    w.show();
    return a.exec();
}

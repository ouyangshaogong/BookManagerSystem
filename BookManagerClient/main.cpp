#include "mainwindow.h"
#include "myapplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MyApplication myApplication;
    myApplication.StartApp(&w);

    w.show();
    return a.exec();

    return 0;
}

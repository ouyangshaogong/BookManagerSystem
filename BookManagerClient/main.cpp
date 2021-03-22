#include "mainwindow.h"
#include "myapplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;
    MainWindow w;
    QObject::connect(&login, &LoginDialog::SendLoginData, &w, &MainWindow::ReceiveLoginData);
    QObject::connect(&w, &MainWindow::SendLoginSuccessData, &login, &LoginDialog::ReceiveLoginSuccessData);

    MyApplication myApplication;
    myApplication.StartApp(&w);

    login.show();


    return a.exec();
}

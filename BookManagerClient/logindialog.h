#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void SendLoginData(QString &strAccount, QString &strPasswd);

public slots:
    void ReceiveLoginButton();
    void ReceiveQuitButton();
    void ReceiveLoginSuccessData(int nRet);
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H

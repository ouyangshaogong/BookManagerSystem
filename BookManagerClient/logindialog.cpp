#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setWindowTitle("登录");

    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::ReceiveLoginButton);
    connect(ui->btnQuit, &QPushButton::clicked, this, &LoginDialog::ReceiveQuitButton);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::ReceiveLoginButton()
{
    QString strAccount = ui->lineEditAccount->text();
    QString strPasswd = ui->lineEditPasswd->text();

    strAccount = "SX000001";
    strPasswd = "123456";

    emit this->SendLoginData(strAccount, strPasswd);
}

void LoginDialog::ReceiveQuitButton()
{
    this->reject();
}

void LoginDialog::ReceiveLoginSuccessData(int nRet)
{
    this->hide();
}

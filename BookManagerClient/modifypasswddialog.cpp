#include "modifypasswddialog.h"
#include "ui_modifypasswddialog.h"

ModifyPasswdDialog::ModifyPasswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPasswdDialog)
{
    ui->setupUi(this);

    setWindowTitle(QString("修改密码"));

    connect(ui->pushButtonOK, &QPushButton::clicked, this, &ModifyPasswdDialog::OnPushButtonOK);
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &ModifyPasswdDialog::OnPushButtonBack);

}

ModifyPasswdDialog::~ModifyPasswdDialog()
{
    delete ui;
}

void ModifyPasswdDialog::OnPushButtonOK()
{
    QString strOldPasswd = ui->oldLineEdit->text();
    QString strNewPasswd = ui->newLineEdit->text();
    QString strRepeatPasswd = ui->repeatLineEdit->text();

    emit this->SendPasswdData(strOldPasswd, strNewPasswd, strRepeatPasswd);

    this->accept();
}

void ModifyPasswdDialog::OnPushButtonBack()
{
    this->reject();
}

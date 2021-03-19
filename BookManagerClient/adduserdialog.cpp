#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include <QStringList>
#include <QDebug>

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    qDebug() << "AddUserDialog::AddUserDialog";

    ui->setupUi(this);

    //设置对话框标题
    setWindowTitle("添加用户");
    //设置固定大小
    setFixedSize(QSize(270, 300));
    ui->comboBoxUserType->addItems(QStringList() << "管理员" << "普通读者" << "游客");

    connect(ui->BtnOK, &QPushButton::clicked, this, [=](){
        UserModel userModel;
        userModel.SetUserName(ui->lineEditName->text().toUtf8().data());
        userModel.SetSex(ui->lineEditSex->text().toUtf8().data());
        userModel.SetBirth(ui->lineEditBirth->text().toUtf8().data());
        userModel.SetPhone(ui->lineEditPhone->text().toUtf8().data());
        userModel.SetAddress(ui->lineEditAddress->text().toUtf8().data());
        userModel.SetUserType(ui->comboBoxUserType->currentIndex());

        emit this->SendAddUser(userModel);

        this->accept();
        qDebug() << "点确定,对话框关闭了";
    });

    connect(ui->BtnCancel, &QPushButton::clicked, this, [=](){
        this->reject();
        qDebug() << "点取消, 对话框关闭了";
    });
}

AddUserDialog::~AddUserDialog()
{
    qDebug() << "AddUserDialog析构了";
    delete ui;
}

#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include "usermodel.h"

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

signals:
    void SendAddUser(UserModel userModel);

private:
    Ui::AddUserDialog *ui;

};

#endif // ADDUSERDIALOG_H

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

    void GetUserType(QString &strText);
    void GetUserID(int maxUserID);
signals:
    void SendAddUser(UserModel userModel);

private:
    Ui::AddUserDialog *ui;
    int m_nMaxUserID;
};

#endif // ADDUSERDIALOG_H

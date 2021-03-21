#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include "usermodel.h"
#include "IDMaker.h"

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
    void GetMaxUserID(int nUserID);
signals:
    void SendAddUser(UserModel userModel);

private:
    Ui::AddUserDialog *ui;
    IDMaker m_nIdMaker;
};

#endif // ADDUSERDIALOG_H

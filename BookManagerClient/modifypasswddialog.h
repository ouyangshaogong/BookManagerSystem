#ifndef MODIFYPASSWDDIALOG_H
#define MODIFYPASSWDDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

namespace Ui {
class ModifyPasswdDialog;
}

class ModifyPasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPasswdDialog(QWidget *parent = nullptr);
    ~ModifyPasswdDialog();

signals:
    void SendPasswdData(QString strOldPasswd, QString strNewPasswd, QString strRepeatPasswd);

public slots:
    void OnPushButtonOK();
    void OnPushButtonBack();

private:
    Ui::ModifyPasswdDialog *ui;
};

#endif // MODIFYPASSWDDIALOG_H

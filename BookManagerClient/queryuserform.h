#ifndef QUERYUSERFORM_H
#define QUERYUSERFORM_H

#include <QWidget>
#include <QResizeEvent>
#include "usermodel.h"
#include <QLayout>
#include <QTableWidgetItem>
#include <QListWidgetItem>
namespace Ui {
class QueryUserForm;
}

class QueryUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit QueryUserForm(QWidget *parent = nullptr);
    ~QueryUserForm();

    void LayoutWidget();
    void SetWidgetHeader();
    void UpdateTableUserData(int currentRow);
public slots:
    void ReceiveUserData(set<UserModel> setUserData);
    void DisplayUserData(QListWidgetItem *item);
private:
    Ui::QueryUserForm *ui;
    QHBoxLayout *m_layout;
    set<UserModel> m_tableCache;
};

#endif // QUERYUSERFORM_H

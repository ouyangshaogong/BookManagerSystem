#ifndef QUERYUSERFORM_H
#define QUERYUSERFORM_H

#include <QWidget>
#include <QResizeEvent>
#include "usermodel.h"
#include <QLayout>
#include <QTableWidgetItem>
#include <QListWidgetItem>
namespace Ui {
class UserManagerWidget;
}

class UserManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserManagerWidget(QWidget *parent = nullptr);
    ~UserManagerWidget();

    void LayoutWidget();

    void UpdateTableUserData(int currentRow);
public slots:
    void GetWidgetHeader(QStringList &strListHeader, QStringList &strTableHeader);
    void ReceiveUserData(set<UserModel> setUserData);
    void DisplayUserData(QListWidgetItem *item);
private:
    Ui::UserManagerWidget *ui;
    QHBoxLayout *m_layout;
    set<UserModel> m_tableCache;
};

#endif // QUERYUSERFORM_H

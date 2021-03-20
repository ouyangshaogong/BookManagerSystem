#ifndef QUERYUSERFORM_H
#define QUERYUSERFORM_H

#include <QWidget>
#include <QResizeEvent>
#include "usermodel.h"
#include "loginhistorymodel.h"
#include <QLayout>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QStringList>
#include <QMouseEvent>
#include <QEvent>
#include <QMenu>
#include <QDialog>
#include <QTextEdit>
#include <map>
#include <QClipboard>
#include "SystemOperateCmd.h"


using namespace std;



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
    void SearchTableUserData(int currentRow, QString &strText);
    void UpdateTableLoginHistory(int currentRow);
    void SearchTableLoginHistory(int currentRow, QString &strText);

public slots:
    void GetWidgetHeader(const int &nOpType, QStringList &strListHeader, QStringList &strTableHeader);
    void ReceiveUserData(set<UserModel> &setUserData);
    void ReceiveLoginHistory(set<LoginHistoryModel> &setLoginData);
    void DisplayUserManagerData(QListWidgetItem *item);
    void DisplayUserOperate();
    void ReceiveSearchText(int nCmdOp, QString &strText);

    void DeleteItemAction();
    void CopyRowItemAction();
    void QueryDetailAction();
private:
    Ui::UserManagerWidget *ui;
    QHBoxLayout *m_layout;
    set<UserModel> m_tableUserCache;
    set<LoginHistoryModel> m_tableLoginCache;
    QStringList m_strOpTypList;
    int m_nOpType;

    typedef void (UserManagerWidget::*pUpdateOperateData)(int);
    map<int, pUpdateOperateData> m_nCmdMapUpdateOpData;

    QMenu *m_rightButtonMenu;
    QAction *m_deleteItemAction;
    QAction *m_copyRowItemAction;
    int m_nColomuCount;
    QAction *m_queryDetailItemAction;
    QStringList m_strTableHeader;
};

#endif // QUERYUSERFORM_H

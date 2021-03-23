#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include <QDebug>
#include "commonmsg.h"
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QTableWidget>
#include <QString>
#include <QStringList>
#include <QSplitter>
#include <QListWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>

#include "adduserdialog.h"
#include "UserManagerWidget.h"
#include "usermodel.h"
#include "bookmodel.h"
#include "lendlistmodel.h"
#include "loginhistorymodel.h"
#include "searchbox.h"
#include "searchcondition.h"
#include "modifypasswddialog.h"
#include "SystemOperateCmd.h"
#include "IDMaker.h"
#include "logindialog.h"
#include "mytablewidget.h"

#define BOOK_CENTER_WIDGET "BookCenterWidget"
#define USER_CENTER_WIDGET "UserCenterWidget"
#define LEND_CENTER_WIDGET "LendCenterWidget"

class MainWindow : public QMainWindow, public View
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual list<int> &ReceiveMsg();
    virtual void HandleNotifyCation(NotifyMsg notifydata);
    void SendCmdMsg();

protected:
    //showEvent事件在窗体显示后才触发
    void showEvent(QShowEvent *evt);

public:
    void InitializeMainWindow();

    void AddMenuBar();
    void ReSizeAndPos();
    void AddMenu();
    void AddMenuAction();

    void AddToolBar();
    void AddToolAction(QString strCenterWidget, const int nCmdOp);

    void AddStatusBar();
    void AddStatusInfo();
    void UpdateStatusBar(QString &loginUser, QString &lastOp);

    void InitializeCenterWidget();
    void SetBookCenterWidget();
    void SetUserCenterWidget();
    void SetLendListCenterWidget();
    void SetCenterWidget(QString strCenterWidget, const int nCmdOp);

    void InitializeConnect();


public:
    void DisplayAddUser(QString &strRet);
    void DisplayDeleteUserByUserID(QString &strRet);
    void DisplayModifyUser(QString &str);
    void DisplayQueryAllUser(set<UserModel> &setUserData, QString &strRet);
    void DisplayAddUserType(QString &strRet);
    void DisplayLoginHistory(set<LoginHistoryModel> &setLoginData, QString &strRet);
    void DisplayDeleteLoginHistory(QString &strRet);
    void DisplayLendList(set<LendListModel> &setLendList, int nRet);

    void DisplayAddBook(QString &str);
    void DisplayDeleteBook(QString &str);
    void DisplayModifyBook(QString &str);
    void DisplayModifyPasswd(QString &strRet);
    void DisplayQueryBook(QString &str);
    void DisplayQueryAllBook(set<BookModel> &setUserData, QString &strRet);
    void DisplayLogin(int nCardType, int nRet);
    void UpdateBookCache();
    void UpdateBookCache(QString strText);

    void UpdateLendCache();
    void UpdateLendCache(QString strText);

    void AddSearchBox();
    void AddSearchCond();
    void SetSearchCondVisible(int nOpType);

    void AddLendBook(int lendType, LendListModel &lendList);
private:
    QMenuBar *m_menuBar;
    QMenu *m_userMgrMenu;
    QMenu *m_bookMgrMenu;
    QMenu *m_LendMgrMenu;


    QAction *m_addUserAction;
    AddUserDialog *m_addUserDlg;

    QAction *m_deleteUserAction;
    QAction *m_modifyUserAction;
    QAction *m_modifyPasswdAction;
    QAction *m_queryUserAction;
    QAction *m_queryLoginAction;

    QAction *m_addBookAction;
    QAction *m_modifyBookAction;
    QAction *m_queryBookAction;

    QAction *m_lendListAction;

    QMenu *m_rightButtonListMenu;
    QAction *m_borrowBookAction;
    QAction *m_precontractBookAction;
    QAction *m_deleteBookAction;

    QToolBar *m_toolBarDynamic;
    QToolBar *m_toolBarStatic;
    QToolBar *m_toolBarCondition;
    QStatusBar *m_statusBar;

    //中心部件
    UserManagerWidget *m_userMgrWiget;
    MyTableWidget *m_tableWidgetBook;
    MyTableWidget *m_tableWidgetLendList;
    map<QString, QWidget*> m_stringMapCenterWidget;
    QString m_strCenterWidget;
    int m_nCmdOperate;

    //图书缓存
    set<BookModel> m_tableCacheBook;
    QStringList m_bookClass;
    SearchBox *m_searchBox;
    SearchCondition *m_searchCondPublish;
    SearchCondition *m_searchCondLanguage;
    SearchCondition *m_searchCondClass;

    set<LendListModel> m_tableCacheLend;
    QStringList m_strLendStateList;
    vector<QPushButton*> m_savedeleteButton;

    vector<QAction*> m_saveNeedDelAction;

    bool m_bIsConnItemChanged;
    bool m_bIsFirstShowStatus;
    QLabel * m_labelTime;
    QLabel * m_labelUser;
    QLabel * m_labelLastOp;

    QString m_strUser;
    map<int, QString> m_mapLastOp;


private:
    QStringList m_strListBookLabels;

    QString m_strLendUser;
    QString m_strLendBook;
    QString m_strLendDate;
    QString m_strBackDate;
    QString m_strLendState;
    QString m_strDeleteLend;

signals:
    void SendQueryUserData(set<UserModel> &setUserData);
    void SendLoginHistory(set<LoginHistoryModel> &setLoginData);
    void SendUserHeader(const int &nOpType, QStringList &strListHeader, QStringList &strTableHeader);
    void SendSearchText(int nCmdOp, QString &strText);
    void SendAddUserData(UserModel userModel);

    void SendCondPublishData(QStringList &strTextList);
    void SendCondLanguageData(QStringList &strTextList);
    void SendCondClassData(QStringList &strTextList);

    void SendLoginSuccessData(int nRet);
public slots:

    void AddUserAction();
    void SetUserCacheMaxUserID(int nMaxUserID);

    void ModifyUserAction();
    void ModifyPasswdAction();
    void QueryUserAction();
    void QueryAllUserAction();
    void QueryLoginHistoryAction();

    void AddBookAction();
    void DeleteBookAction();
    void ModifyBookAction();
    void QueryBookAction();
    void QueryAllBookAction();

    void QueryLendListAction();

    void ReceiveAddUser(UserModel userModel);
    void ReceivePasswdData(QString strOldPasswd, QString strNewPasswd, QString strRepeatPasswd);
    void ReceiveCellDouble(int row, int column);
    void ReceiveCellChanged(int row, int column);
    void DoSearchBook(QString strText);

    void ReceiveUserType(int userType, QString &strText);
    void ReceiveDeleteUserData(int userid);
    void ReceiveDeleteLoginHistory(QString &strAcount);

    void ReceiveComboBoxData(const QString &strText);

    void ReceiveModifyUserData(int userid, int nAttrType, QString strText);

    void ReceiveLoginData(QString &strAccount, QString &strPasswd);

    void UpdateStatusTime();

    void ReceiveRightButton();
    void ReceivePrecontractBook();
    void ReceiveBorrowBook();
};
#endif // MAINWINDOW_H

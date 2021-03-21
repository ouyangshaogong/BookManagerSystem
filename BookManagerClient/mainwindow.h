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
#include "adduserdialog.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>

#include "UserManagerWidget.h"
#include "usermodel.h"
#include "bookmodel.h"
#include "loginhistorymodel.h"
#include "searchbox.h"
#include "searchcondition.h"
#include "modifypasswddialog.h"
#include "SystemOperateCmd.h"
#include "IDMaker.h"

#define BOOK_CENTER_WIDGET "BookCenterWidget"
#define USER_CENTER_WIDGET "UserCenterWidget"

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

    void InitializeCenterWidget();
    void SetBookCenterWidget();
    void SetUserCenterWidget();
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

    void DisplayAddBook(QString &str);
    void DisplayDeleteBook(QString &str);
    void DisplayModifyBook(QString &str);
    void DisplayModifyPasswd(QString &strRet);
    void DisplayQueryBook(QString &str);
    void DisplayQueryAllBook(set<BookModel> &setUserData, QString &strRet);
    void UpdateBookCache();
    void UpdateBookCache(QString strText);

    void AddSearchBox();
    void AddSearchCond();
    void SetSearchCondVisible(int nOpType);
private:
    QMenuBar *m_menuBar;
    QMenu *m_userMgrMenu;
    QMenu *m_bookMgrMenu;


    QAction *m_addUserAction;
    AddUserDialog *m_addUserDlg;

    QAction *m_deleteUserAction;
    QAction *m_modifyUserAction;
    QAction *m_modifyPasswdAction;
    QAction *m_queryUserAction;
    QAction *m_queryLoginAction;

    QAction *m_addBookAction;
    QAction *m_deleteBookAction;
    QAction *m_modifyBookAction;
    QAction *m_queryBookAction;

    QToolBar *m_toolBarDynamic;
    QToolBar *m_toolBarStatic;
    QToolBar *m_toolBarCondition;
    QStatusBar *m_statusBar;

    //中心部件
    UserManagerWidget *m_queryUser;
    QTableWidget *m_tableWidgetBook;
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

    vector<QAction*> m_saveNeedDelAction;
private:
    QString m_strLabelName;
    QString m_strLabelAuthor;
    QString m_strLabelPublish;
    QString m_strLabelISBN;
    QString m_strLabelLanguage;
    QString m_strLabelPrice;
    QString m_strLabelPubDate;
    QString m_strLabelClass;
    QString m_strLabelNumber;
    QString m_strLabelIntro;

signals:
    void SendQueryUserData(set<UserModel> &setUserData);
    void SendLoginHistory(set<LoginHistoryModel> &setLoginData);
    void SendUserHeader(const int &nOpType, QStringList &strListHeader, QStringList &strTableHeader);
    void SendSearchText(int nCmdOp, QString &strText);
    void SendAddUserData(UserModel userModel);

    void SendCondPublishData(QStringList &strTextList);
    void SendCondLanguageData(QStringList &strTextList);
    void SendCondClassData(QStringList &strTextList);
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

    void ReceiveAddUser(UserModel userModel);
    void ReceivePasswdData(QString strOldPasswd, QString strNewPasswd, QString strRepeatPasswd);
    void ReceiveCellDouble(int row, int column);
    void ReceiveCellChanged(int row, int column);
    void DoSearchBook(QString strText);

    void ReceiveUserType(int userType, QString &strText);
    void ReceiveDeleteUserData(int userid);
    void ReceiveDeleteLoginHistory(QString &strAcount);

    void ReceiveComboBoxData(const QString &strText);
};
#endif // MAINWINDOW_H

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
#include "UserManagerWidget.h"
#include "usermodel.h"
#include "bookmodel.h"
#include "searchbox.h"
#include "modifypasswddialog.h"
#include "SystemOperateCmd.h"

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
    void AddToolAction(QString strCenterWidget);

    void AddStatusBar();
    void AddStatusInfo();

    void InitializeCenterWidget();
    void SetBookCenterWidget();
    void SetUserCenterWidget();
    void SetCenterWidget(QString strCenterWidget);

    void InitializeConnect();


public:
    void DisplayAddUser(QString &strRet);
    void DisplayDeleteUser(QString &str);
    void DisplayModifyUser(QString &str);
    void DisplayQueryAllUser(set<UserModel> &setUserData, QString &strRet);

    void DisplayAddBook(QString &str);
    void DisplayDeleteBook(QString &str);
    void DisplayModifyBook(QString &str);
    void DisplayModifyPasswd(QString &strRet);
    void DisplayQueryBook(QString &str);
    void DisplayQueryAllBook(set<BookModel> &setUserData, QString &strRet);
    void UpdateBookCache();
    void UpdateBookCache(QString strText);

    void AddSearchBox();

private:
    QMenuBar *m_menuBar;
    QMenu *m_userMgrMenu;
    QMenu *m_bookMgrMenu;

    QAction *m_addUserAction;
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
    QStatusBar *m_statusBar;

    //中心部件
    UserManagerWidget *m_queryUser;
    QTableWidget *m_tableWidgetBook;
    map<QString, QWidget*> m_stringMapCenterWidget;

    //图书缓存
    set<BookModel> m_tableCacheBook;
    vector<QString> m_bookClass;
    SearchBox *m_searchBox;

    bool m_isAddUserExist;
    bool m_isAddBookExist;
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
    void SendUserData(set<UserModel> setUserData);
    void SendUserHeader(const int &nOpType, QStringList &strListHeader, QStringList &strTableHeader);
public slots:

    void AddUserAction();
    void DeleteUserAction();
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
    void DoSearchBook(QString strText);
};
#endif // MAINWINDOW_H

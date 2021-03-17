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
#include "adduserdialog.h"


class MainWindow : public QMainWindow, public View
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual list<int> ReceiveMsg();
    virtual void HandleNotifyCation(NotifyMsg notifydata);

public:
    void AddMenuBar();
    void ReSizeAndPos();
    void AddMenu();
    void AddMenuAction();

    void AddToolBar();
    void AddToolAction();

    void AddStatusBar();
    void AddStatusInfo();

    void SetCenterWidget();

    void AddUserAction();
    void DeleteUserAction();
    void ModifyUserAction();
    void QueryUserAction();

    void AddBookAction();
    void DeleteBookAction();
    void ModifyBookAction();
    void QueryBookAction();

    void DisplayAddUser(QString &str);
    void DisplayDeleteUser(QString &str);
    void DisplayModifyUser(QString &str);
    void DisplayQueryUser(QString &str);

    void DisplayAddBook(QString &str);
    void DisplayDeleteBook(QString &str);
    void DisplayModifyBook(QString &str);
    void DisplayQueryBook(QString &str);

private:
    QMenuBar *m_menuBar;
    QMenu *m_userMgrMenu;
    QMenu *m_bookMgrMenu;

    QAction *m_addUserAction;
    QAction *m_deleteUserAction;
    QAction *m_modifyUserAction;
    QAction *m_queryUserAction;

    QAction *m_addBookAction;
    QAction *m_deleteBookAction;
    QAction *m_modifyBookAction;
    QAction *m_queryBookAction;

    QToolBar *m_toolBar;
    QStatusBar *m_statusBar;
    QTableWidget *m_tableWidget;

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

public slots:
    void ReceiveAddUser(UserModel userModel);

};
#endif // MAINWINDOW_H

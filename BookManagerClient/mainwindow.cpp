#include "mainwindow.h"
#include <QDesktopWidget>
#include "datacommonfunc.h"
#include <QString>
#include <QSplitter>

PACKAGEPARAMETER(MainWin)
PARSEPARAMETER(MainWin)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_strLabelName.append("书名");
    m_strLabelAuthor.append("作者");
    m_strLabelPublish.append("出版社");
    m_strLabelISBN.append("ISBN");
    m_strLabelLanguage.append("语言");
    m_strLabelPrice.append("价格");
    m_strLabelPubDate.append("出版日期");
    m_strLabelClass.append("分类");
    m_strLabelNumber.append("剩余数量");
    m_strLabelIntro.append("简介");

    InitializeCenterWidget();
    //重绘大小和位置
    ReSizeAndPos();
    //添加菜单栏
    AddMenuBar();
    //创建菜单
    AddMenu();
    //创建菜单项
    AddMenuAction();
    //添加工具栏
    AddToolBar();
    //为工具栏添加action
    AddToolAction();
    //为action添加功能

    //添加状态栏
    AddStatusBar();
    //为状态栏添加widget
    AddStatusInfo();

    //设置中心部件
    SetCenterWidget(BOOK_CENTER_WIDGET);

    //查询用户信息
    QueryAllUserAction();

    //添加用户
    AddUserAction();
    //删除用户
    //DeleteUserAction();
    //修改用户信息
    //ModifyUserAction();


    AddBookAction();
    //DeleteBookAction();
    //ModifyBookAction();
    QueryAllBookAction();


}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow析构了";
}


list<int> MainWindow::ReceiveMsg()
{
    list<int> listMsg;
    listMsg.push_back(MSG_ADDLEVEL);

    listMsg.push_back(MSG_ADDUSER);
    listMsg.push_back(MSG_DELETEUSER);
    listMsg.push_back(MSG_MODIFYUSER);
    listMsg.push_back(MSG_QUERYUSER);
    listMsg.push_back(MSG_QUERYALLUSER);

    listMsg.push_back(MSG_ADDBOOK);
    listMsg.push_back(MSG_DELETEBOOK);
    listMsg.push_back(MSG_MODIFYBOOK);
    listMsg.push_back(MSG_QUERYBOOK);
    listMsg.push_back(MSG_QUERYALLBOOK);

    return listMsg;
}

void MainWindow::HandleNotifyCation(NotifyMsg notify)
{

    qDebug() << "MainWindow::HandleNotifyCation>>" << QString::number(notify.GetMapParam().size());

    switch(notify.nMsg)
    {
        case MSG_ADDLEVEL:
        {
            int *p;// = (int*)notify.pCommonData;
            qDebug() << "LEVEL:" << QString().number(*p);
            break;
        }
        case MSG_ADDUSER:
        {
            int nRet = 0;
            QString str;
            ParseParamMainWin(notify.GetMapParam(), nRet);
            str = QString::number(nRet);
            DisplayAddUser(str);
            break;
        }
        case MSG_DELETEUSER:
        {
            int nRet = 0;
            QString str;
            ParseParamMainWin(notify.GetMapParam(), nRet);
            str = QString::number(nRet);
            DisplayDeleteUser(str);
            break;
        }
        case MSG_MODIFYUSER:
        {
            int nRet = 0;
            QString str;
            ParseParamMainWin(notify.GetMapParam(), nRet);
            str = QString::number(nRet);
            DisplayModifyUser(str);
            break;
        }
        case MSG_QUERYALLUSER:
        {
            int nRet = 0;
            QString strRet;
            set<UserModel> setUserData;
            ParseParamMainWin(notify.GetMapParam(), setUserData, nRet);
            strRet = QString::number(nRet);
            DisplayQueryUser(setUserData, strRet);
            break;
        }
        case MSG_ADDBOOK:
            //DisplayAddBook(str);
            break;
        case MSG_DELETEBOOK:
            //DisplayDeleteBook(str);
            break;
        case MSG_MODIFYBOOK:
            //DisplayModifyBook(str);
            break;
        case MSG_QUERYALLBOOK:
        {
            int nRet = 0;
            QString strRet;
            set<BookModel> setBookData;
            ParseParamMainWin(notify.GetMapParam(), setBookData, nRet);
            strRet = QString::number(nRet);
            DisplayQueryAllBook(setBookData, strRet);
            break;
        }
        default:
            break;
    }
}

void MainWindow::ReSizeAndPos()
{
    resize(1000, 800);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

void MainWindow::AddMenuBar()
{
    m_menuBar = menuBar();
    setMenuBar(m_menuBar);
}

void MainWindow::AddMenu()
{
    m_userMgrMenu = m_menuBar->addMenu("用户管理");
    m_bookMgrMenu = m_menuBar->addMenu("图书管理");
}

void MainWindow::AddMenuAction()
{
    m_addUserAction = m_userMgrMenu->addAction("添加用户");
    m_userMgrMenu->addSeparator();
    //m_deleteUserAction = m_userMgrMenu->addAction("删除用户");
    //m_userMgrMenu->addSeparator();
    //m_modifyUserAction = m_userMgrMenu->addAction("修改用户");
    //m_userMgrMenu->addSeparator();
    m_queryUserAction = m_userMgrMenu->addAction("查询用户");

    m_addBookAction = m_bookMgrMenu->addAction("添加图书");
    m_bookMgrMenu->addSeparator();
    //m_deleteBookAction = m_bookMgrMenu->addAction("删除图书");
    //m_bookMgrMenu->addSeparator();
    //m_modifyBookAction = m_bookMgrMenu->addAction("修改图书");
    //m_bookMgrMenu->addSeparator();
    m_queryBookAction = m_bookMgrMenu->addAction("查询图书");
}

void MainWindow::AddToolBar()
{
    m_toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, m_toolBar);

    //只允许停靠在上面
    m_toolBar->setAllowedAreas( Qt::TopToolBarArea);

    //设置为不浮动
    m_toolBar->setFloatable(false);

    //设置移动 (总开关)
    m_toolBar->setMovable(false);
}

void MainWindow::AddToolAction()
{
    //工具栏中可以设置内容
    m_toolBar->addAction(m_addUserAction);
    //添加分割线
    m_toolBar->addSeparator();
    //m_toolBar->addAction(m_deleteUserAction);
    //m_toolBar->addSeparator();
    //m_toolBar->addAction(m_modifyUserAction);
    //m_toolBar->addSeparator();
    m_toolBar->addAction(m_queryUserAction);
    m_toolBar->addSeparator();

    //工具栏中可以设置内容
    m_toolBar->addAction(m_addBookAction);
    //添加分割线
    m_toolBar->addSeparator();
    //m_toolBar->addAction(m_deleteBookAction);
    //m_toolBar->addSeparator();
    //m_toolBar->addAction(m_modifyBookAction);
    //m_toolBar->addSeparator();
    m_toolBar->addAction(m_queryBookAction);
}

void MainWindow::AddStatusBar()
{
    m_statusBar = new QStatusBar();
    setStatusBar(m_statusBar);
}

void MainWindow::AddStatusInfo()
{
    //放标签控件
    QLabel * labelTime = new QLabel("时间",this);
    m_statusBar->addWidget(labelTime);

    QLabel * labelStatus = new QLabel("状态",this);
    m_statusBar->addWidget(labelStatus);

    QLabel * labelLastOp = new QLabel("上一个操作",this);
    m_statusBar->addPermanentWidget(labelLastOp);
}

void MainWindow::SetBookCenterWidget()
{
    //设置中心部件 只能一个
    m_tableWidgetBook = new QTableWidget(this);
    //设置列数
    m_tableWidgetBook->setColumnCount(10);
    //设置水平表头
    QStringList strListLabels;
    strListLabels.append(m_strLabelName);
    strListLabels.append(m_strLabelAuthor);
    strListLabels.append(m_strLabelPublish);
    strListLabels.append(m_strLabelISBN);
    strListLabels.append(m_strLabelLanguage);
    strListLabels.append(m_strLabelPrice);
    strListLabels.append(m_strLabelPubDate);
    strListLabels.append(m_strLabelClass);
    strListLabels.append(m_strLabelNumber);
    strListLabels.append(m_strLabelIntro);

    m_tableWidgetBook->setHorizontalHeaderLabels(strListLabels);

    m_stringMapCenterWidget.insert(map<string, QWidget*>::value_type(BOOK_CENTER_WIDGET, m_tableWidgetBook));
}

void MainWindow::SetUserCenterWidget()
{
    m_queryUser = new QueryUserForm;
    m_queryUser->resize(this->width(), this->height());
    m_stringMapCenterWidget.insert(map<string, QWidget*>::value_type(USER_CENTER_WIDGET, m_queryUser));
}

void MainWindow::UpdateUserCenterWidget()
{

}

void MainWindow::InitializeCenterWidget()
{
    SetBookCenterWidget();
    SetUserCenterWidget();
    connect(this, &MainWindow::SendUserData, m_queryUser, &QueryUserForm::ReceiveUserData);
}

void MainWindow::SetCenterWidget(string strCenterWidget)
{
//    map<string, QWidget*>::iterator iter = m_stringMapCenterWidget.find(strCenterWidget);
//    if(iter != m_stringMapCenterWidget.end())
//    {
//        setCentralWidget(iter->second);
//    }

    if (strCenterWidget == BOOK_CENTER_WIDGET)
    {
        setCentralWidget(m_tableWidgetBook);
    }
    else if (strCenterWidget == USER_CENTER_WIDGET)
    {
        setCentralWidget(m_queryUser);
    }

}

void MainWindow::AddUserAction()
{
    qDebug() << "MainWindow::AddUserAction" << endl;
    connect(m_addUserAction, &QAction::triggered, this, [=](){
        //先弹框，然后等待用户输入
        AddUserDialog addUserDlg(this);
        void(AddUserDialog:: *sendsig)(UserModel) = &AddUserDialog::SendAddUser;
        void(MainWindow:: *receiveSlot)(UserModel)  = &MainWindow::ReceiveAddUser;
        connect(&addUserDlg, sendsig, this, receiveSlot);
        if (addUserDlg.exec() == QDialog::Accepted)
        {
            qDebug() << "Accepted" << endl;
        }
        else
        {
            qDebug() << "Rejected" << endl;
        }
    });
}

void MainWindow::DeleteUserAction()
{
    connect(m_deleteUserAction, &QAction::triggered,[=](){
        //通过userid删除用户
        int userid = 10;
        NotifyMsg notify;
        notify.nMsg = MSG_DELETEUSER;
        PackageParamMainWin(notify.GetMapParam(), userid);
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
}

void MainWindow::ModifyUserAction()
{

    connect(m_modifyUserAction, &QAction::triggered,[=](){

        int userid = 2;
        string address = "纽约";
        NotifyMsg notify;
        notify.nMsg = MSG_MODIFYUSER;
        PackageParamMainWin(notify.GetMapParam(), userid, address);
        //通过userid修改用户地址address
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
}

//查询所有用户，界面只显示５００条数据
void MainWindow::QueryAllUserAction()
{
    connect(m_queryUserAction, &QAction::triggered,[=](){
        SetCenterWidget(USER_CENTER_WIDGET);
        NotifyMsg notify;
        notify.nMsg = MSG_QUERYALLUSER;
        PackageParamMainWin(notify.GetMapParam());
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
}

void MainWindow::QueryUserAction()
{

}


void MainWindow::AddBookAction()
{
    connect(m_addBookAction, &QAction::triggered,[=](){
        NotifyMsg notify;
        notify.nMsg = MSG_ADDBOOK;
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
}

void MainWindow::DeleteBookAction()
{
    connect(m_deleteBookAction, &QAction::triggered,[=](){
        NotifyMsg notify;
        notify.nMsg = MSG_DELETEBOOK;
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
}

void MainWindow::ModifyBookAction()
{
    connect(m_modifyBookAction, &QAction::triggered,[=](){
        NotifyMsg notify;
        notify.nMsg = MSG_MODIFYBOOK;
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
}

void MainWindow::QueryAllBookAction()
{
    connect(m_queryBookAction, &QAction::triggered,[=](){
        SetCenterWidget(BOOK_CENTER_WIDGET);
        NotifyMsg notify;
        notify.nMsg = MSG_QUERYALLBOOK;
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
}

void MainWindow::QueryBookAction()
{

}

void MainWindow::DisplayAddUser(QString &str)
{
    qDebug() << "DisplayAddUser:" << str;
}

void MainWindow::DisplayDeleteUser(QString &str)
{
    qDebug() << "DisplayDeleteUser:" << str.toUtf8().data();
}

void MainWindow::DisplayModifyUser(QString &str)
{
    qDebug() << "DisplayModifyUser:" << str.toUtf8().data();
}

void MainWindow::DisplayQueryUser(set<UserModel> &setUserData, QString &strRet)
{
    qDebug() << "DisplayQueryUser:" << strRet.toUtf8().data();
    emit this->SendUserData(setUserData);
}


void MainWindow::DisplayAddBook(QString &str)
{
    qDebug() << "DisplayAddBook:" << str.toUtf8().data();
}

void MainWindow::DisplayDeleteBook(QString &str)
{
    qDebug() << "DisplayDeleteBook:" << str.toUtf8().data();
}

void MainWindow::DisplayModifyBook(QString &str)
{
    qDebug() << "DisplayModifyBook:" << str.toUtf8().data();
}

void MainWindow::DisplayQueryAllBook(set<BookModel> &setBookData, QString &strRet)
{
    qDebug() << "DisplayQueryBook:" << strRet.toUtf8().data();
    m_tableWidgetBook->setRowCount(setBookData.size());
    m_tableCacheBook.insert(setBookData.begin(), setBookData.end());
    UpdateBookCache();


}

void MainWindow::UpdateBookCache()
{
    set<BookModel>::iterator iter = m_tableCacheBook.begin();

    int nRow = 0;
    for (; iter != m_tableCacheBook.end(); ++iter)
    {
        BookModel bookata = *iter;

        m_tableWidgetBook->setItem(nRow, 0, new QTableWidgetItem(QString(bookata.GetName().c_str())));
        m_tableWidgetBook->setItem(nRow, 1, new QTableWidgetItem(QString(bookata.GetAuthor().c_str())));
        m_tableWidgetBook->setItem(nRow, 2, new QTableWidgetItem(QString(bookata.GetPublish().c_str())));
        m_tableWidgetBook->setItem(nRow, 3, new QTableWidgetItem(QString(bookata.GetISBN().c_str())));
        m_tableWidgetBook->setItem(nRow, 4, new QTableWidgetItem(QString(bookata.GetLanguage().c_str())));
        m_tableWidgetBook->setItem(nRow, 5, new QTableWidgetItem(QString::number(bookata.GetPrice())));
        m_tableWidgetBook->setItem(nRow, 6, new QTableWidgetItem(QString(bookata.GetPubDate().c_str())));
        m_tableWidgetBook->setItem(nRow, 7, new QTableWidgetItem(QString("暂无分类")));
        m_tableWidgetBook->setItem(nRow, 8, new QTableWidgetItem(QString::number(bookata.GetNumber())));
        m_tableWidgetBook->setItem(nRow, 9, new QTableWidgetItem(QString(bookata.GetIntroduction().c_str())));
        nRow++;
    }
}

void MainWindow::ReceiveAddUser(UserModel userModel)
{
    qDebug() << "MainWindow::ReceiveAddUser" << endl;
    NotifyMsg notify;
    notify.nMsg = MSG_ADDUSER;
    PackageParamMainWin(notify.GetMapParam(), userModel);
    qDebug() << "DataController::handleEvent>>" << notify.nMsg << QString::number(notify.GetMapParam().size());
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}


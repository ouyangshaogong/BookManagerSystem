#include "mainwindow.h"
#include <QDesktopWidget>
#include "datacommonfunc.h"
#include <QString>
#include <QSplitter>
#include <QHeaderView>
#include "searchbox.h"

PACKAGEPARAMETER(MainWin)
PARSEPARAMETER(MainWin)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    m_strListBookLabels.append("书名");
    m_strListBookLabels.append("作者");
    m_strListBookLabels.append("出版社");
    m_strListBookLabels.append("ISBN");
    m_strListBookLabels.append("语言");
    m_strListBookLabels.append("价格");
    m_strListBookLabels.append("出版日期");
    m_strListBookLabels.append("分类");
    m_strListBookLabels.append("剩余数量");
    m_strListBookLabels.append("简介");


    m_strLendUser.append("借阅用户");
    m_strLendBook.append("借阅图书");
    m_strLendDate.append("借阅日期");
    m_strBackDate.append("归还日期");
    m_strLendState.append("借阅状态");
    m_strDeleteLend.append("删除借阅");

    m_strLendStateList << "预约" << "借阅" << "归还" << "续借" << "催还";

    m_bookClass.append("马克思主义");
    m_bookClass.append("哲学");
    m_bookClass.append("社会科学总论");
    m_bookClass.append("政治法律");
    m_bookClass.append("军事");
    m_bookClass.append("经济");
    m_bookClass.append("文化");
    m_bookClass.append("计算机科学技术");
    m_bookClass.append("文学");
    m_bookClass.append("艺术");

    m_mapLastOp.insert(map<int, QString>::value_type(MSG_LOGINSYSTEM, "登录"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_ADDUSER, "添加用户"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_DELETEUSER, "删除用户"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_MODIFYUSER, "修改用户信息"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_QUERYUSER, "查看用户信息"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_QUERYALLUSER, "查询所有用户信息"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_MODIFYPASSWD, "修改密码"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_LOGINHISTORY, "查看登录历史"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_ADDUSERTYPE, "添加用户类型"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_DELETELOGINHISTORY, "删除登录历史"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_ADDBOOK, "添加图书"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_DELETEBOOK, "删除图书"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_MODIFYBOOK, "修改图书信息"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_QUERYBOOK, "查看图书信息"));
    m_mapLastOp.insert(map<int, QString>::value_type(MSG_QUERYALLBOOK, "查询所有图书信息"));

    m_bIsFirstShowStatus = false;
    m_bIsConnItemChanged = false;

    InitializeMainWindow();
    InitializeConnect();


}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow析构了";
}



list<int> &MainWindow::ReceiveMsg()
{
    m_listMsg.push_back(MSG_ADDLEVEL);

    m_listMsg.push_back(MSG_ADDUSER);
    m_listMsg.push_back(MSG_DELETEUSER);
    m_listMsg.push_back(MSG_MODIFYUSER);
    m_listMsg.push_back(MSG_MODIFYPASSWD);
    m_listMsg.push_back(MSG_QUERYUSER);
    m_listMsg.push_back(MSG_QUERYALLUSER);
    m_listMsg.push_back(MSG_LOGINHISTORY);
    m_listMsg.push_back(MSG_DELETELOGINHISTORY);
    m_listMsg.push_back(MSG_ADDUSERTYPE);
    m_listMsg.push_back(MSG_LOGINSYSTEM);
    m_listMsg.push_back(MSG_QUERYLENDLIST);
    m_listMsg.push_back(MSG_ADDLENDLIST);


    m_listMsg.push_back(MSG_ADDBOOK);
    m_listMsg.push_back(MSG_DELETEBOOK);
    m_listMsg.push_back(MSG_MODIFYBOOK);
    m_listMsg.push_back(MSG_QUERYBOOK);
    m_listMsg.push_back(MSG_QUERYALLBOOK);

    return m_listMsg;
}

void MainWindow::HandleNotifyCation(NotifyMsg notify)
{

    qDebug() << "MainWindow::HandleNotifyCation>>BEGIN>>notify.nMsg:>>" << notify.nMsg << "notify>>size:";

    switch(notify.nMsg)
    {
        case MSG_ADDLEVEL:
        {
            break;
        }
        case MSG_ADDUSER:
        {
            int nRet = 0;
            ParseParamMainWin(notify, nRet);
            QString strRet = QString::number(nRet);
            DisplayAddUser(strRet);
            break;
        }
        case MSG_DELETEUSER:
        {
            int nRet = 0;
            ParseParamMainWin(notify, nRet);
            QString strRet = QString::number(nRet);
            DisplayDeleteUserByUserID(strRet);
            break;
        }
        case MSG_MODIFYUSER:
        {
            int nRet = 0;
            QString str;
            ParseParamMainWin(notify, nRet);
            str = QString::number(nRet);
            DisplayModifyUser(str);
            break;
        }
        case MSG_MODIFYPASSWD:
        {
            int nRet = 0;
            ParseParamMainWin(notify, nRet);
            QString strRet = QString::number(nRet);
            DisplayModifyUser(strRet);
            break;
        }
        case MSG_QUERYALLUSER:
        {
            int nRet = 0;
            QString strRet;
            set<UserModel> setUserData;
            ParseParamMainWin(notify, setUserData, nRet);
            strRet = QString::number(nRet);
            DisplayQueryAllUser(setUserData, strRet);
            break;
        }
        case MSG_ADDUSERTYPE:
        {
            int nRet = 0;
            ParseParamMainWin(notify, nRet);
            QString strRet = QString::number(nRet);
            DisplayAddUserType(strRet);
            break;
        }
        case MSG_LOGINHISTORY:
        {
            int nRet = 0;
            set<LoginHistoryModel> setLoginHistory;
            ParseParamMainWin(notify, setLoginHistory, nRet);
            QString strRet = QString::number(nRet);
            DisplayLoginHistory(setLoginHistory, strRet);
            break;
        }
        case MSG_DELETELOGINHISTORY:
        {
            int nRet = 0;
            ParseParamMainWin(notify, nRet);
            QString strRet = QString::number(nRet);
            DisplayDeleteLoginHistory(strRet);
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
            ParseParamMainWin(notify, setBookData, nRet);
            strRet = QString::number(nRet);
            DisplayQueryAllBook(setBookData, strRet);
            break;
        }
        case MSG_LOGINSYSTEM:
        {
            int nCardType = 0;
            int nRet = 0;
            ParseParamMainWin(notify, nCardType, nRet);
            DisplayLogin(nCardType, nRet);
            break;
        }
        case MSG_QUERYLENDLIST:
        {
            set<LendListModel> setLendList;
            int nRet = 0;
            ParseParamMainWin(notify, setLendList, nRet);
            DisplayLendList(setLendList, nRet);
            break;
        }
        case MSG_ADDLENDLIST:
        {
            int nRet = 0;
            ParseParamMainWin(notify, nRet);
            DisplayAddLendList(nRet);
            break;
        }
        default:
            break;
    }

    map<int, QString>::iterator iter = m_mapLastOp.find(notify.nMsg);
    if (iter != m_mapLastOp.end())
    {
        UpdateStatusBar(m_strUser, iter->second);
    }

}

void MainWindow::SendCmdMsg()
{
    NotifyMsg notify;
    notify.nMsg = MSG_QUERYALLBOOK;
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::showEvent(QShowEvent *evt)
{
    //在窗口出现之后，显示图书数据
    QueryAllBookAction();
}

void MainWindow::InitializeMainWindow()
{
    setWindowTitle("图书管理系统");
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

    //添加状态栏
    AddStatusBar();
    //为状态栏添加widget
    AddStatusInfo();

    InitializeCenterWidget();

    AddSearchBox();
    AddSearchCond();

    QTimer *timer = new QTimer(this);
    timer->start(1000); //每隔1000ms发送timeout的信号
    connect(timer, SIGNAL(timeout()),this, SLOT(UpdateStatusTime()));
}

void MainWindow::ReSizeAndPos()
{
    resize(1200, 800);
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
    m_LendMgrMenu = m_menuBar->addMenu("借阅管理");
}

void MainWindow::AddMenuAction()
{
    m_addUserAction = new QAction("添加用户");
    m_modifyPasswdAction = new QAction("修改密码");
    m_queryUserAction = m_userMgrMenu->addAction("用户");
    m_userMgrMenu->addSeparator();
    m_queryLoginAction = m_userMgrMenu->addAction("历史登录");

    m_addBookAction = m_bookMgrMenu->addAction("添加图书");
    m_bookMgrMenu->addSeparator();
    m_queryBookAction = m_bookMgrMenu->addAction("查询图书");

    m_lendListAction = m_LendMgrMenu->addAction("查询借阅日志");
}

void MainWindow::AddToolBar()
{
    m_toolBarDynamic = new QToolBar(this);
    //只允许停靠在上面
    m_toolBarDynamic->setAllowedAreas( Qt::TopToolBarArea);
    //设置为不浮动
    m_toolBarDynamic->setFloatable(false);
    //设置移动 (总开关)
    m_toolBarDynamic->setMovable(false);
    addToolBar(Qt::TopToolBarArea, m_toolBarDynamic);


    m_toolBarStatic = new QToolBar(this);
    //只允许停靠在上面
    m_toolBarStatic->setAllowedAreas( Qt::TopToolBarArea);
    //设置为不浮动
    m_toolBarStatic->setFloatable(false);
    //设置不移动 (总开关)
    m_toolBarStatic->setMovable(false);
    addToolBar(Qt::TopToolBarArea, m_toolBarStatic);


    m_toolBarCondition = new QToolBar(this);
    //只允许停靠在上面
    m_toolBarCondition->setAllowedAreas( Qt::TopToolBarArea);
    //设置为不浮动
    m_toolBarCondition->setFloatable(false);
    //设置不移动 (总开关)
    m_toolBarCondition->setMovable(false);
    addToolBar(Qt::TopToolBarArea, m_toolBarCondition);
}

void MainWindow::AddToolAction(QString strCenterWidget, const int nCmdOp)
{
    //清理上次切换加到工具栏的action
    for (int i = 0; i < m_saveNeedDelAction.size(); ++i)
    {
        m_toolBarDynamic->removeAction(m_saveNeedDelAction[i]);
    }
    m_saveNeedDelAction.clear();

    if (strCenterWidget == BOOK_CENTER_WIDGET)
    {
        m_toolBarDynamic->addAction(m_addBookAction);
        m_saveNeedDelAction.push_back(m_addBookAction);
    }
    else if (strCenterWidget == USER_CENTER_WIDGET)
    {
        if (nCmdOp == OPERATE_QUERY_USER_DATA)
        {
            m_toolBarDynamic->addAction(m_addUserAction);
            m_toolBarDynamic->addAction(m_modifyPasswdAction);
            m_saveNeedDelAction.push_back(m_addUserAction);
            m_saveNeedDelAction.push_back(m_modifyPasswdAction);
        }
        else if (nCmdOp == OPERATE_QUERY_LOGIN_HISTORY)
        {
        }

    }
}

void MainWindow::AddStatusBar()
{
    m_statusBar = new QStatusBar();
    setStatusBar(m_statusBar);
}

void MainWindow::AddStatusInfo()
{
    //放标签控件
    m_labelTime = new QLabel("", this);
    m_labelUser = new QLabel("", this);
    m_labelLastOp = new QLabel("", this);

    m_statusBar->addWidget(m_labelTime);
    m_statusBar->addWidget(m_labelUser);
    m_statusBar->addPermanentWidget(m_labelLastOp);
}

void MainWindow::UpdateStatusTime()
{
    QDateTime dtime = QDateTime::currentDateTime();
    QString loginTime = dtime.toString("yyyy年MM月dd日 hh:mm:ss");

    m_labelTime->setText(loginTime);
}

void MainWindow::UpdateStatusBar(QString &loginUser, QString &lastOp)
{

    m_labelUser->setText(loginUser);
    m_labelLastOp->setText(lastOp);
}

void MainWindow::SetBookCenterWidget()
{
    //设置中心部件 只能一个
    m_tableWidgetBook = new MyTableWidget(this);
    //设置列数
    m_tableWidgetBook->setColumnCount(10);
    //设置水平表头
    m_tableWidgetBook->setHorizontalHeaderLabels(m_strListBookLabels);

    //自适应列宽和设置自动等宽
    m_tableWidgetBook->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_stringMapCenterWidget.insert(map<QString, QWidget*>::value_type(BOOK_CENTER_WIDGET, m_tableWidgetBook));
}

void MainWindow::SetLendListCenterWidget()
{
    //设置中心部件 只能一个
    m_tableWidgetLendList = new MyTableWidget;
    //设置列数
    m_tableWidgetLendList->setColumnCount(6);
    //设置水平表头
    QStringList strListLabels;
    strListLabels.append(m_strLendUser);
    strListLabels.append(m_strLendBook);
    strListLabels.append(m_strLendDate);
    strListLabels.append(m_strBackDate);
    strListLabels.append(m_strLendState);
    strListLabels.append(m_strDeleteLend);

    m_tableWidgetLendList->setHorizontalHeaderLabels(strListLabels);

    //自适应列宽和设置自动等宽
    m_tableWidgetLendList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_stringMapCenterWidget.insert(map<QString, QWidget*>::value_type(LEND_CENTER_WIDGET, m_tableWidgetLendList));
}

void MainWindow::SetUserCenterWidget()
{
    m_addUserDlg = new AddUserDialog(this);
    m_userMgrWiget = new UserManagerWidget;
    m_userMgrWiget->resize(this->width(), this->height());
    m_stringMapCenterWidget.insert(map<QString, QWidget*>::value_type(USER_CENTER_WIDGET, m_userMgrWiget));
}

void MainWindow::InitializeCenterWidget()
{
    SetBookCenterWidget();
    SetUserCenterWidget();
    SetLendListCenterWidget();
    connect(this, &MainWindow::SendUserHeader, m_userMgrWiget, &UserManagerWidget::GetWidgetHeader);
    connect(this, &MainWindow::SendQueryUserData, m_userMgrWiget, &UserManagerWidget::ReceiveQueryUserData);
    connect(this, &MainWindow::SendAddUserData, m_userMgrWiget, &UserManagerWidget::ReceiveAddUserData);
    connect(this, &MainWindow::SendLoginHistory, m_userMgrWiget, &UserManagerWidget::ReceiveLoginHistory);

    //删除登录历史
    connect(m_userMgrWiget, &UserManagerWidget::SendDeleteLoginHistory, this, &MainWindow::ReceiveDeleteLoginHistory);
    //删除用户数据
    connect(m_userMgrWiget, &UserManagerWidget::SendDeleteUserData, this, &MainWindow::ReceiveDeleteUserData);
    //发送用户缓存最大ID
    connect(m_userMgrWiget, &UserManagerWidget::SendUerCacheMaxUserID, this, &MainWindow::SetUserCacheMaxUserID);
    //添加用户类型
    connect(m_userMgrWiget, &UserManagerWidget::SendUserType, this, &MainWindow::ReceiveUserType);
}

void MainWindow::SetCenterWidget(QString strCenterWidget, const int nCmdOp)
{

    m_strCenterWidget = strCenterWidget;
    m_nCmdOperate = nCmdOp;
    //为工具栏添加action
    AddToolAction(strCenterWidget, nCmdOp);
    //设置条件透明
    SetSearchCondVisible(nCmdOp);

    //去掉原来的中心部件
    takeCentralWidget();
    map<QString, QWidget*>::iterator iter = m_stringMapCenterWidget.find(strCenterWidget);
    if(iter != m_stringMapCenterWidget.end())
    {
        setCentralWidget(iter->second);
    }
}

void MainWindow::InitializeConnect()
{
    connect(m_addUserAction, &QAction::triggered, this, &MainWindow::AddUserAction);
    connect(m_queryUserAction, &QAction::triggered, this, &MainWindow::QueryAllUserAction);
    connect(m_userMgrWiget, &UserManagerWidget::SendModifyUserData, this, &MainWindow::ReceiveModifyUserData);
    connect(m_queryLoginAction, &QAction::triggered, this, &MainWindow::QueryLoginHistoryAction);

    connect(m_modifyPasswdAction, &QAction::triggered, this, &MainWindow::ModifyPasswdAction);
    connect(m_queryBookAction, &QAction::triggered, this, &MainWindow::QueryAllBookAction);

    //查询借阅日志
    connect(m_lendListAction, &QAction::triggered, this, &MainWindow::QueryLendListAction);

    //双击单元格
    connect(m_tableWidgetBook, &MyTableWidget::cellDoubleClicked, this, &MainWindow::ReceiveCellDouble);

    //右击单元格
    connect(m_tableWidgetBook, &MyTableWidget::SendRightButton, this, &MainWindow::ReceiveRightButton);

}

void MainWindow::AddUserAction()
{
    qDebug() << "MainWindow::AddUserAction" << endl;
    void(AddUserDialog:: *sendsig)(UserModel) = &AddUserDialog::SendAddUser;
    void(MainWindow:: *receiveSlot)(UserModel)  = &MainWindow::ReceiveAddUser;
    connect(m_addUserDlg, sendsig, this, receiveSlot);
    if (m_addUserDlg->exec() == QDialog::Accepted)
    {
        qDebug() << "Accepted" << endl;
    }
    else
    {
        qDebug() << "Rejected" << endl;
    }
}

void MainWindow::SetUserCacheMaxUserID(int nMaxUserID)
{
    m_addUserDlg->GetMaxUserID(nMaxUserID);
}

void MainWindow::ModifyUserAction()
{

}

void MainWindow::ModifyPasswdAction()
{
    ModifyPasswdDialog modifyPasswddlg(this);


    if (modifyPasswddlg.exec() == QDialog::Accepted)
    {
        qDebug() << "Accepted" << endl;
    }
    else
    {
        qDebug() << "Rejected" << endl;
    }
}

//查询所有用户，界面只显示５００条数据
void MainWindow::QueryAllUserAction()
{
    SetCenterWidget(USER_CENTER_WIDGET, OPERATE_QUERY_USER_DATA);

    QStringList strListHeader;
    strListHeader << "管理员" << "普通读者" << "游客";

    QStringList strTableHeader;
    strTableHeader.append("用户姓名");
    strTableHeader.append("性别");
    strTableHeader.append("生日");
    strTableHeader.append("家庭地址");
    strTableHeader.append("电话");

    this->SendUserHeader(OPERATE_QUERY_USER_DATA, strListHeader, strTableHeader);

    NotifyMsg notify;
    notify.nMsg = MSG_QUERYALLUSER;
    PackageParamMainWin(notify);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::QueryLoginHistoryAction()
{
    qDebug() << "MainWindow::QueryLoginHistoryAction" << endl;
    SetCenterWidget(USER_CENTER_WIDGET, OPERATE_QUERY_LOGIN_HISTORY);

    QStringList strListHeader;
    strListHeader << "正在登录" << "历史登录";

    QStringList strTableHeader;
    strTableHeader.append("登录帐号");
    strTableHeader.append("登录IP");
    strTableHeader.append("登录端口");
    strTableHeader.append("登录开始时间");
    strTableHeader.append("登录结束时间");
    strTableHeader.append("登录持续秒数");
    strTableHeader.append("登录持续天数");

    this->SendUserHeader(OPERATE_QUERY_LOGIN_HISTORY, strListHeader, strTableHeader);

    NotifyMsg notify;
    notify.nMsg = MSG_LOGINHISTORY;
    PackageParamMainWin(notify);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::QueryUserAction()
{

}


void MainWindow::AddBookAction()
{
}

void MainWindow::DeleteBookAction()
{
}

void MainWindow::ModifyBookAction()
{
}

void MainWindow::QueryLendListAction()
{
    SetCenterWidget(LEND_CENTER_WIDGET, OPERATE_LEND_NONE);
    NotifyMsg notify;
    notify.nMsg = MSG_QUERYLENDLIST;
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::QueryAllBookAction()
{
    qDebug() << "MainWindow::QueryAllBookAction";
    //当查询所有图书信息完成后，触发单元格发生改变事件
    if (m_bIsConnItemChanged)
    {
        disconnect(m_tableWidgetBook, &MyTableWidget::cellChanged, this, &MainWindow::ReceiveCellChanged);
    }

    SetCenterWidget(BOOK_CENTER_WIDGET, OPERATE_BOOK_CONDITION);
    NotifyMsg notify;
    notify.nMsg = MSG_QUERYALLBOOK;
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::QueryBookAction()
{

}

void MainWindow::DisplayAddUser(QString &strRet)
{
    qDebug() << "DisplayAddUser>>strRet:" << strRet;
}

void MainWindow::DisplayDeleteUserByUserID(QString &strRet)
{
    qDebug() << "DisplayDeleteUserByUserID>>strRet:" << strRet.toUtf8().data();
}

void MainWindow::DisplayModifyUser(QString &str)
{
    qDebug() << "DisplayModifyUser>>strRet:" << str.toUtf8().data();
}

void MainWindow::DisplayModifyPasswd(QString &strRet)
{
    qDebug() << "DisplayModifyPasswd>>strRet:" << strRet.toUtf8().data();
}

void MainWindow::DisplayQueryAllUser(set<UserModel> &setUserData, QString &strRet)
{
    qDebug() << "MainWindow::DisplayQueryAllUser>>strRet:" << strRet.toUtf8().data();
    emit this->SendQueryUserData(setUserData);
}

void MainWindow::DisplayAddUserType(QString &strRet)
{
    qDebug() << "MainWindow::DisplayAddUserType>>strRet:" << strRet.toUtf8().data();
}

void MainWindow::DisplayLoginHistory(set<LoginHistoryModel> &setLoginData, QString &strRet)
{
    qDebug() << "DisplayLoginHistory:>>strRet" << strRet.toUtf8().data();
    emit this->SendLoginHistory(setLoginData);
}

void MainWindow::DisplayDeleteLoginHistory(QString &strRet)
{
    qDebug() << "DisplayDeleteLoginHistory>>strRet:" << strRet.toUtf8().data();
}


void MainWindow::DisplayAddBook(QString &str)
{
    qDebug() << "DisplayAddBook>>strRet:" << str.toUtf8().data();
}

void MainWindow::DisplayDeleteBook(QString &str)
{
    qDebug() << "DisplayDeleteBook>>strRet:" << str.toUtf8().data();
}

void MainWindow::DisplayModifyBook(QString &str)
{
    qDebug() << "DisplayModifyBook>>strRet:" << str.toUtf8().data();
}

void MainWindow::DisplayQueryAllBook(set<BookModel> &setBookData, QString &strRet)
{
    qDebug() << "DisplayQueryBook>>strRet:" << strRet.toUtf8().data();
    m_tableCacheBook.clear();
    m_tableCacheBook.insert(setBookData.begin(), setBookData.end());
    m_tableWidgetBook->setRowCount(m_tableCacheBook.size());
    UpdateBookCache();

    //当查询所有图书信息完成后，触发单元格发生改变事件
    if (!m_bIsConnItemChanged)
    {
        connect(m_tableWidgetBook, &MyTableWidget::cellChanged, this, &MainWindow::ReceiveCellChanged);
        m_bIsConnItemChanged = true;
    }
}

void MainWindow::DisplayAddLendList(int nRet)
{
    if (nRet == 0)
    {
        QueryLendListAction();

    }
    else
    {
        QMessageBox::information(this,"info","预约失败");
    }
}

void MainWindow::DisplayLendList(set<LendListModel> &setLendList, int nRet)
{
    qDebug() << "MainWindow::DisplayLendList>>setLendList.size:" << setLendList.size();

    for (int i = 0; i < m_tableCacheLend.size(); i++)
    {
        m_tableWidgetLendList->removeCellWidget(i, 5);
        delete m_savedeleteButton[i];
    }
    m_savedeleteButton.clear();
    m_tableCacheLend.clear();

    m_tableCacheLend.insert(setLendList.begin(), setLendList.end());

    m_tableWidgetLendList->setRowCount(m_tableCacheLend.size());
    UpdateLendWidgetCache();
}

void MainWindow::DisplayLogin(int nCardType, int nRet)
{
    if (nRet == 0)
    {
        this->show();
        emit this->SendLoginSuccessData(nRet);
    }
    else
    {
        QMessageBox::information(this,"info","登录失败");
    }
}

void MainWindow::UpdateLendWidgetCache()
{
    m_tableWidgetLendList->clearContents();

    //根据userid查找username，根据bookid查找bookname

    int nRow = 0;
    set<LendListModel>::iterator iter = m_tableCacheLend.begin();
    for (; iter != m_tableCacheLend.end(); ++iter)
    {
        LendListModel lendata = *iter;

        QPushButton *deleteBtn = new QPushButton();
        //设置ｂｕｔｔｏｎ透明
        deleteBtn->setFlat(true);
        if (lendata.GetLendState() == LendPreContract
            || lendata.GetLendState() == LendBorrow)
        {
            deleteBtn->setEnabled(false);
        }

        m_savedeleteButton.push_back(deleteBtn);
        deleteBtn->setText("删除");
        m_tableWidgetLendList->setCellWidget(nRow, 5, deleteBtn);

        m_tableWidgetLendList->setItem(nRow, 0, new QTableWidgetItem(QString::number(lendata.GetUserID())));
        m_tableWidgetLendList->setItem(nRow, 1, new QTableWidgetItem(QString::number(lendata.GetBookID())));
        m_tableWidgetLendList->setItem(nRow, 2, new QTableWidgetItem(QString(lendata.GetLendDate().c_str())));
        m_tableWidgetLendList->setItem(nRow, 3, new QTableWidgetItem(QString(lendata.GetBackDate().c_str())));
        m_tableWidgetLendList->setItem(nRow, 4, new QTableWidgetItem(m_strLendStateList[lendata.GetLendState()]));

        nRow++;
    }


}

void MainWindow::UpdateBookCache(QString strText)
{
    //清空所有内容
    m_tableWidgetBook->clearContents();
    set<BookModel>::iterator iter = m_tableCacheBook.begin();

    int nRow = 0;
    for (; iter != m_tableCacheBook.end(); ++iter)
    {
        BookModel bookata = *iter;
        qDebug() << "MainWindow::UpdateBookCache>>strText:" << strText << "BookClass:" << m_bookClass[bookata.GetClassID()];
        if (strText.toUtf8().data() == bookata.GetName() || strText.toUtf8().data() == bookata.GetAuthor()
            || strText.toUtf8().data() == bookata.GetPublish() || strText.toUtf8().data() == bookata.GetISBN()
            || strText.toUtf8().data() == bookata.GetLanguage() || strText == QString::number(bookata.GetPrice())
            || strText.toUtf8().data() == bookata.GetPubDate() || strText == m_bookClass[bookata.GetClassID()]
            || strText.toUtf8().data() == QString::number(bookata.GetNumber()
            || strText.toUtf8().data() == bookata.GetIntroduction()))
        {
            m_tableWidgetBook->setItem(nRow, 0, new QTableWidgetItem(QString(bookata.GetName().c_str())));
            m_tableWidgetBook->setItem(nRow, 1, new QTableWidgetItem(QString(bookata.GetAuthor().c_str())));
            m_tableWidgetBook->setItem(nRow, 2, new QTableWidgetItem(QString(bookata.GetPublish().c_str())));
            m_tableWidgetBook->setItem(nRow, 3, new QTableWidgetItem(QString(bookata.GetISBN().c_str())));
            m_tableWidgetBook->setItem(nRow, 4, new QTableWidgetItem(QString(bookata.GetLanguage().c_str())));
            m_tableWidgetBook->setItem(nRow, 5, new QTableWidgetItem(QString::number(bookata.GetPrice())));
            m_tableWidgetBook->setItem(nRow, 6, new QTableWidgetItem(QString(bookata.GetPubDate().c_str())));
            m_tableWidgetBook->setItem(nRow, 7, new QTableWidgetItem(m_bookClass[bookata.GetClassID()]));
            m_tableWidgetBook->setItem(nRow, 8, new QTableWidgetItem(QString::number(bookata.GetNumber())));
            m_tableWidgetBook->setItem(nRow, 9, new QTableWidgetItem(QString(bookata.GetIntroduction().c_str())));
            nRow++;
        }


    }
}

void MainWindow::UpdateBookCache()
{
    m_tableWidgetBook->clearContents();
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
        m_tableWidgetBook->setItem(nRow, 7, new QTableWidgetItem(m_bookClass[bookata.GetClassID()]));
        m_tableWidgetBook->setItem(nRow, 8, new QTableWidgetItem(QString::number(bookata.GetNumber())));
        m_tableWidgetBook->setItem(nRow, 9, new QTableWidgetItem(QString(bookata.GetIntroduction().c_str())));
        nRow++;
    }
}

void MainWindow::ReceiveAddUser(UserModel userModel)
{
    emit this->SendAddUserData(userModel);
    qDebug() << "MainWindow::ReceiveAddUser" << endl;
    NotifyMsg notify;
    notify.nMsg = MSG_ADDUSER;
    PackageParamMainWin(notify, userModel);
    qDebug() << "DataController::handleEvent>>" << notify.nMsg;
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::ReceiveCellChanged(int row, int column)
{
    QTableWidgetItem *item = m_tableWidgetBook->item(row, column);

    bool *IsIntAttr = new bool;
    *IsIntAttr = false;
    int nAttr = 0;
    if (column == BOOK_ATTR_CLASS || column == BOOK_ATTR_PRICE || column == BOOK_ATTR_NUMBER)
    {
        nAttr = item->text().toInt();
        *IsIntAttr = true;
    }

    NotifyMsg notify;
    notify.nMsg = MSG_MODIFYBOOK;
    notify.pExtra = (void*)IsIntAttr;
    if (*IsIntAttr)
    {
        PackageParamMainWin(notify, row, column, nAttr);
    }
    else
    {
        //row相当于bookid column相当于属性类型
        PackageParamMainWin(notify, row, column, item->text());
    }

    qDebug() << "MainWindow::ReceiveCellChanged>>" << notify.nMsg;
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::ReceiveBorrowBook()
{

}

void MainWindow::ReceivePrecontractBook()
{
    //添加一条预约借阅数据
    //获取userid,获取bookid,生成开始时间
    QString strText;
    int currentRow = m_tableWidgetBook->currentRow();
    //获取书名项
    QTableWidgetItem *item = m_tableWidgetBook->item(currentRow, 0);
    strText += item->text();
    //查找bookid
    int bookid = 0;
    set<BookModel>::iterator iter = m_tableCacheBook.begin();
    for (; iter != m_tableCacheBook.end(); ++iter)
    {
        BookModel bookdata = *iter;
        QString strName = bookdata.GetName().c_str();
        if (strName == strText)
        {
            bookid = bookdata.GetBookID();
            break;
        }
    }

    //查找readerid
    int readerid = 0;
//    set<>::iterator iter = m_tableCacheBook.begin();
//    for (; iter != m_tableCacheBook.end(); ++iter)
//    {
//        BookModel bookdata = *iter;
//        if (bookdata.GetName().c_str() == strText)
//        {
//            bookid = bookdata.GetBookID();
//            break;
//        }
//    }

    LendListModel lendList;
    lendList.SetBookID(bookid);
    lendList.SetUserID(readerid);

    QDateTime dtime = QDateTime::currentDateTime();
    QString loginTime = dtime.toString("yyyy-MM-dd");
    lendList.SetLendDate(loginTime.toUtf8().data());
    lendList.SetLendState(LendPreContract);

    NotifyMsg notify;
    notify.nMsg = MSG_ADDLENDLIST;
    PackageParamMainWin(notify, lendList);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::ReceiveRightButton()
{
    m_rightButtonListMenu = new QMenu(this);
    m_precontractBookAction = new QAction("预约", m_rightButtonListMenu);
    m_rightButtonListMenu->addAction(m_precontractBookAction);
    m_borrowBookAction = new QAction("借书", m_rightButtonListMenu);
    m_rightButtonListMenu->addAction(m_borrowBookAction);
    m_deleteBookAction = new QAction("删除", m_rightButtonListMenu);
    m_rightButtonListMenu->addAction(m_deleteBookAction);
    //触发复制该行操作
    connect(m_precontractBookAction, &QAction::triggered, this, &MainWindow::ReceivePrecontractBook);

    //让菜单显示的位置在鼠标的坐标上
    m_rightButtonListMenu->move(cursor().pos());
    m_rightButtonListMenu->show();
}

void MainWindow::ReceiveCellDouble(int row, int column)
{
    qDebug() << "MainWindow::ReceiveCellDouble";

    if (column == 9)
    {
        QDialog *dlg = new QDialog(this);
        dlg->resize(300, 300);
        dlg->setWindowTitle("简介");

        QTextEdit *textEdit = new QTextEdit(dlg);
        textEdit->resize(300, 300);
        //设置为只读
        textEdit->setReadOnly(true);

        //获取单元格的数据，并显示到textEdit
        QString strIntro = m_tableWidgetBook->item(row, column)->text();
        textEdit->setText(strIntro);

        dlg->show();
        dlg->setAttribute(Qt::WA_DeleteOnClose); //55号 属性
        qDebug() << "双击显示简介对话框弹出了";
    }
}

void MainWindow::DoSearchBook(QString strText)
{
    qDebug() << "MainWindow::DoSearchBook";

    if (m_strCenterWidget == USER_CENTER_WIDGET)
    {
        emit this->SendSearchText(m_nCmdOperate, strText);
    }
    else if (m_strCenterWidget == BOOK_CENTER_WIDGET)
    {
        if (strText.isEmpty())
        {
            UpdateBookCache();
        }
        else
        {
            UpdateBookCache(strText);
        }
    }
}

void MainWindow::ReceiveUserType(int userType, QString &strText)
{
    m_addUserDlg->GetUserType(strText);
    NotifyMsg notify;
    notify.nMsg = MSG_ADDUSERTYPE;
    PackageParamMainWin(notify, userType, strText);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::ReceiveDeleteUserData(int userid)
{
    NotifyMsg notify;
    notify.nMsg = MSG_DELETEUSER;
    PackageParamMainWin(notify, userid);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::ReceiveDeleteLoginHistory(QString &strAcount)
{
    NotifyMsg notify;
    notify.nMsg = MSG_DELETELOGINHISTORY;
    PackageParamMainWin(notify, strAcount);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::ReceiveComboBoxData(const QString &strText)
{
    DoSearchBook(strText);
}

void MainWindow::ReceiveModifyUserData(int userid, int nAttrType, QString strText)
{
    NotifyMsg notify;
    notify.nMsg = MSG_MODIFYUSER;
    PackageParamMainWin(notify, userid, nAttrType, strText);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::ReceiveLoginData(QString &strAccount, QString &strPasswd)
{
    NotifyMsg notify;
    notify.nMsg = MSG_LOGINSYSTEM;
    m_strUser = strAccount;
    PackageParamMainWin(notify, strAccount, strPasswd);
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}

void MainWindow::SetSearchCondVisible(int nOpType)
{
    m_toolBarCondition->setVisible(true);

    if (nOpType != OPERATE_BOOK_CONDITION)
    {
        m_toolBarCondition->setVisible(false);
    }
}

void MainWindow::AddSearchCond()
{
    //添加其他搜索条件
    m_searchCondPublish = new SearchCondition(this);
    m_searchCondPublish->setLabelText(m_strListBookLabels[2] + ":");
    m_searchCondPublish->setDefaultComboText(5);
    m_toolBarCondition->addWidget(m_searchCondPublish);
    connect(this, &MainWindow::SendCondPublishData, m_searchCondPublish, &SearchCondition::GetComboBoxText);
    connect(m_searchCondPublish, &SearchCondition::SendComboBoxText, this, &MainWindow::ReceiveComboBoxData);


    QStringList strTextList;
    strTextList << "培生" << "汤姆森路透" << "里德爱斯维尔" << "威科" << "企鹅兰登书屋";
    strTextList << "中国南方出版传媒集团" << "阿歇特图书" << "麦格希教育" << "环球出版集团";
    emit this->SendCondPublishData(strTextList);


    m_searchCondLanguage = new SearchCondition(this);
    m_searchCondLanguage->setLabelText(m_strListBookLabels[4] + ":");
    m_searchCondLanguage->setDefaultComboText(8);
    m_toolBarCondition->addWidget(m_searchCondLanguage);
    connect(this, &MainWindow::SendCondLanguageData, m_searchCondLanguage, &SearchCondition::GetComboBoxText);
    connect(m_searchCondLanguage, &SearchCondition::SendComboBoxText, this, &MainWindow::ReceiveComboBoxData);

    strTextList.clear();
    strTextList << "中文" << "英文" << "日文" << "韩文" << "法文";
    strTextList << "俄语" << "意大利语" << "波斯文" << "梵语" << "土耳其文";
    emit this->SendCondLanguageData(strTextList);


    m_searchCondClass = new SearchCondition(this);
    m_searchCondClass->setLabelText(m_strListBookLabels[7] + ":");
    m_searchCondLanguage->setDefaultComboText(3);
    m_toolBarCondition->addWidget(m_searchCondClass);
    connect(this, &MainWindow::SendCondClassData, m_searchCondClass, &SearchCondition::GetComboBoxText);
    connect(m_searchCondClass, &SearchCondition::SendComboBoxText, this, &MainWindow::ReceiveComboBoxData);
    emit this->SendCondClassData(m_bookClass);

}

void MainWindow::AddSearchBox()
{
    //添加搜索框
    m_searchBox = new SearchBox(this);
    m_toolBarStatic->addWidget(m_searchBox);
    //搜索框
    connect(m_searchBox, &SearchBox::SendLineEditText, this, &MainWindow::DoSearchBook);
    connect(this, &MainWindow::SendSearchText, m_userMgrWiget, &UserManagerWidget::ReceiveSearchText);

}

void MainWindow::ReceivePasswdData(QString strOldPasswd, QString strNewPasswd, QString strRepeatPasswd)
{
    qDebug() << "MainWindow::ReceiveAddUser" << endl;
    NotifyMsg notify;
    notify.nMsg = MSG_MODIFYPASSWD;
    PackageParamMainWin(notify, strOldPasswd, strNewPasswd, strRepeatPasswd);
    qDebug() << "DataController::handleEvent>>" << notify.nMsg;
    DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
}


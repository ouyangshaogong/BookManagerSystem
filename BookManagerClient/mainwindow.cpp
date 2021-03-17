#include "mainwindow.h"
#include <QDesktopWidget>
#include "datacommonfunc.h"
#include "usermodel.h"
#include <QString>

//封装参数递归终止函数
void PackageParamMainWin(map<string, void*> &mapParam)
{
}

//封装参数展开函数
template <class T, class ...Args>
void PackageParamMainWin(map<string, void*> &mapParam, T head, Args... rest)
{
    T *t = new T;
    *t = head;
    mapParam.insert(map<string, void*>::value_type(typeid(head).name(), (void*)t));
    PackageParamMainWin(mapParam, rest...);
}

//解析参数递归终止函数
void ParseParamMainWin(map<string, void*> &mapParam)
{
    mapParam.clear();
    qDebug() << "g_strMapVoid.size:" << mapParam.size();
}

//解析参数展开函数
template <class T, class ...Args>
void ParseParamMainWin(map<string, void*> &mapParam, T &head, Args&... rest)
{
    map<string, void*>::iterator iter = mapParam.find(typeid(T).name());
    if (iter != mapParam.end())
    {
        head = *((T*)iter->second);
    }

    T *t = (T*)iter->second;
    delete t;

    ParseParamMainWin(mapParam, rest...);
}

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
    SetCenterWidget();

    //添加用户
    AddUserAction();
    //删除用户
    DeleteUserAction();
    //修改用户信息
    ModifyUserAction();
    //查询用户信息
    QueryUserAction();

    AddBookAction();
    DeleteBookAction();
    ModifyBookAction();
    QueryBookAction();


}

MainWindow::~MainWindow()
{
}

list<int> MainWindow::ReceiveMsg()
{
    list<int> listMsg;
    listMsg.push_back(MSG_ADDLEVEL);

    listMsg.push_back(MSG_ADDUSER);
    listMsg.push_back(MSG_DELETEUSER);
    listMsg.push_back(MSG_MODIFYUSER);
    listMsg.push_back(MSG_QUERYUSER);

    listMsg.push_back(MSG_ADDBOOK);
    listMsg.push_back(MSG_DELETEBOOK);
    listMsg.push_back(MSG_MODIFYBOOK);
    listMsg.push_back(MSG_QUERYBOOK);

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
        case MSG_QUERYUSER:
        {
            int nRet = 0;
            QString str;
            ParseParamMainWin(notify.GetMapParam(), nRet);
            str = QString::number(nRet);
            DisplayQueryUser(str);
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
        case MSG_QUERYBOOK:
            //DisplayQueryBook(str);
            break;
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
    m_deleteUserAction = m_userMgrMenu->addAction("删除用户");
    m_userMgrMenu->addSeparator();
    m_modifyUserAction = m_userMgrMenu->addAction("修改用户");
    m_userMgrMenu->addSeparator();
    m_queryUserAction = m_userMgrMenu->addAction("查询用户");

    m_addBookAction = m_bookMgrMenu->addAction("添加图书");
    m_bookMgrMenu->addSeparator();
    m_deleteBookAction = m_bookMgrMenu->addAction("删除图书");
    m_bookMgrMenu->addSeparator();
    m_modifyBookAction = m_bookMgrMenu->addAction("修改图书");
    m_bookMgrMenu->addSeparator();
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
    m_toolBar->addAction(m_deleteUserAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_modifyUserAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_queryUserAction);

    //工具栏中可以设置内容
    m_toolBar->addAction(m_addBookAction);
    //添加分割线
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_deleteBookAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_modifyBookAction);
    m_toolBar->addSeparator();
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

void MainWindow::SetCenterWidget()
{
    //设置中心部件 只能一个
    m_tableWidget = new QTableWidget(this);
    setCentralWidget(m_tableWidget);

    //设置列数
    m_tableWidget->setColumnCount(10);
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

    m_tableWidget->setHorizontalHeaderLabels(strListLabels);
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

void MainWindow::QueryUserAction()
{
    connect(m_queryUserAction, &QAction::triggered,[=](){

        string strAuthor("村上春树");
        NotifyMsg notify;
        notify.nMsg = MSG_QUERYUSER;
        PackageParamMainWin(notify.GetMapParam(), strAuthor);
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
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

void MainWindow::QueryBookAction()
{
    connect(m_queryBookAction, &QAction::triggered,[=](){
        NotifyMsg notify;
        notify.nMsg = MSG_QUERYBOOK;
        DataCommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND, notify);
    });
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

void MainWindow::DisplayQueryUser(QString &str)
{
    qDebug() << "DisplayQueryUser:" << str.toUtf8().data();
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

void MainWindow::DisplayQueryBook(QString &str)
{
    qDebug() << "DisplayQueryBook:" << str.toUtf8().data();
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



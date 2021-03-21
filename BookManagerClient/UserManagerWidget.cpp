#include "UserManagerWidget.h"
#include "ui_UserManagerWidget.h"
#include <QDebug>

UserManagerWidget::UserManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagerWidget)
{
    ui->setupUi(this);

    //给QTableWidget安装事件拦截器
    ui->tableWidget->installEventFilter(this);

    m_nCmdMapUpdateOpData[OPERATE_QUERY_USER_DATA] = &UserManagerWidget::UpdateTableUserData;
    m_nCmdMapUpdateOpData[OPERATE_QUERY_LOGIN_HISTORY] = &UserManagerWidget::UpdateTableLoginHistory;
    //按比例布局控件
    LayoutWidget();

    //点击用户类型显示用户数据
    connect(ui->listWidget, &MyListWidget::SendLeftButton, this, &UserManagerWidget::DisplayUserManagerData);

    //listWidget点击用户类型显示用户数据
    connect(ui->listWidget, &MyListWidget::SendRightButton, this, &UserManagerWidget::DisplayUserListOperate);

    //tableWidget右击删除修改操作
    connect(ui->tableWidget, &MyTableWidget::SendRightButton, this, &UserManagerWidget::DisplayUserTableOperate);
    qDebug() << "UserManagerWidget 构造了";
}

UserManagerWidget::~UserManagerWidget()
{
    qDebug() << "UserManagerWidget 析构了";
    delete m_layout;
    delete ui;
}

void UserManagerWidget::GetWidgetHeader(const int &nOpType, QStringList &strListHeader, QStringList &strTableHeader)
{
    qDebug() << "UserManagerWidget::GetWidgetHeader";
    ui->listWidget->clear();
    ui->tableWidget->clear();

    m_nOpType = nOpType;
    ui->listWidget->addItems(strListHeader);
    m_nListColumnCount = strListHeader.size();
    //设置列数
    ui->tableWidget->setColumnCount(strTableHeader.size());
    m_nTableColumnCount = strTableHeader.size();
    m_strTableHeader = strTableHeader;
    //设置水平表头
    ui->tableWidget->setHorizontalHeaderLabels(strTableHeader);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void UserManagerWidget::LayoutWidget()
{
    m_layout = new QHBoxLayout;      // 新建水平布局管理器
    m_layout->addWidget(ui->listWidget);        // 向布局管理器中添加部件
    m_layout->addWidget(ui->tableWidget);

    // 设置部件间的间隔
    m_layout->setSpacing(15);
    // 按比例设置控件位置
    m_layout->setStretch(0, 1);
    m_layout->setStretch(1, 5);
    setLayout(m_layout);
}

void UserManagerWidget::DisplayUserManagerData()
{
    qDebug() << "UserManagerWidget::DisplayUserData>>";

    map<int, pUpdateOperateData>::iterator iter = m_nCmdMapUpdateOpData.find(m_nOpType);
    if (iter != m_nCmdMapUpdateOpData.end())
    {
        (this->*iter->second)(ui->listWidget->currentRow());
    }

}

void UserManagerWidget::DisplayUserListOperate()
{
    if (m_nOpType == OPERATE_QUERY_USER_DATA)
    {
        m_rightButtonListMenu = new QMenu(this);
        m_addUserTypeAction = new QAction("添加用户类型", m_rightButtonListMenu);
        m_rightButtonListMenu->addAction(m_addUserTypeAction);
        //触发复制该行操作
        connect(m_addUserTypeAction, &QAction::triggered, this, &UserManagerWidget::AddUserTypeItemAction);

        //让菜单显示的位置在鼠标的坐标上
        m_rightButtonListMenu->move(cursor().pos());
        m_rightButtonListMenu->show();
    }

}

void UserManagerWidget::DisplayUserTableOperate()
{
    m_rightButtonTableMenu = new QMenu(this);
    m_deleteItemAction = new QAction("删除", m_rightButtonTableMenu);
    m_rightButtonTableMenu->addAction(m_deleteItemAction);
    //触发删除操作
    connect(m_deleteItemAction, &QAction::triggered, this, &UserManagerWidget::DeleteItemAction);

    if (m_nOpType == OPERATE_QUERY_USER_DATA)
    {
        m_copyRowItemAction = new QAction("复制该行", m_rightButtonTableMenu);
        m_rightButtonTableMenu->addAction(m_copyRowItemAction);
        //触发复制该行操作
        connect(m_copyRowItemAction, &QAction::triggered, this, &UserManagerWidget::CopyRowItemAction);
    }
    else if (m_nOpType == OPERATE_QUERY_LOGIN_HISTORY)
    {
        m_queryDetailItemAction = new QAction("查询详细信息", m_rightButtonTableMenu);
        m_rightButtonTableMenu->addAction(m_queryDetailItemAction);
        //触发复制该行操作
        connect(m_queryDetailItemAction, &QAction::triggered, this, &UserManagerWidget::QueryDetailAction);
    }

    m_rightButtonTableMenu->move(cursor().pos()); //让菜单显示的位置在鼠标的坐标上
    m_rightButtonTableMenu->show();
}

void UserManagerWidget::UpdateTableUserData(int currentRow)
{
    //清理tableWidget内容
    ui->tableWidget->clearContents();

    int nRow = 0;
    ui->tableWidget->setRowCount(m_tableUserCache.size());
    set<UserModel>::iterator iter = m_tableUserCache.begin();
    for (; iter != m_tableUserCache.end(); ++iter)
    {
        UserModel userdata = *iter;
        if (userdata.GetUserType() == currentRow)
        {
            ui->tableWidget->setItem(nRow, 0, new QTableWidgetItem(QString(userdata.GetUserName().c_str())));
            //qDebug() << userdata.GetUserName().c_str() << QString::number(ui->listWidget->currentRow());
            ui->tableWidget->setItem(nRow, 1, new QTableWidgetItem(QString(userdata.GetSex().c_str())));
            ui->tableWidget->setItem(nRow, 2, new QTableWidgetItem(QString(userdata.GetBirth().c_str())));
            ui->tableWidget->setItem(nRow, 3, new QTableWidgetItem(QString(userdata.GetAddress().c_str())));
            ui->tableWidget->setItem(nRow, 4, new QTableWidgetItem(QString(userdata.GetPhone().c_str())));
            nRow++;
        }
    }
}

void UserManagerWidget::SearchTableUserData(int currentRow, QString &strText)
{
    int nRow = 0;
    set<UserModel>::iterator iter = m_tableUserCache.begin();
    for (; iter != m_tableUserCache.end(); ++iter)
    {
        UserModel userata = *iter;
        if ((userata.GetUserName().c_str() == strText
            || userata.GetSex().c_str() == strText
            || userata.GetBirth().c_str() == strText
            || userata.GetAddress().c_str() == strText
            || userata.GetPhone().c_str() == strText)
            && currentRow == userata.GetUserType())
        {
            ui->tableWidget->setItem(nRow, 0, new QTableWidgetItem(QString(userata.GetUserName().c_str())));
            ui->tableWidget->setItem(nRow, 1, new QTableWidgetItem(QString(userata.GetSex().c_str())));
            ui->tableWidget->setItem(nRow, 2, new QTableWidgetItem(QString(userata.GetBirth().c_str())));
            ui->tableWidget->setItem(nRow, 3, new QTableWidgetItem(QString(userata.GetAddress().c_str())));
            ui->tableWidget->setItem(nRow, 4, new QTableWidgetItem(QString(userata.GetPhone().c_str())));
            nRow++;
        }

    }
}

void UserManagerWidget::SearchTableLoginHistory(int currentRow, QString &strText)
{
    int nRow = 0;
    set<LoginHistoryModel>::iterator iter = m_tableLoginCache.begin();
    for (; iter != m_tableLoginCache.end(); ++iter)
    {
        LoginHistoryModel loginHistory = *iter;
        if ((loginHistory.GetAccount().c_str() == strText
            || loginHistory.GetIP().c_str() == strText
            || loginHistory.GetPort().c_str() == strText
            || loginHistory.GetBeginTime().c_str() == strText
            || loginHistory.GetEndTime().c_str() == strText
            || loginHistory.GetContinueTimeSec().c_str() == strText
            || loginHistory.GetContinueTimeDay().c_str() == strText)
            && currentRow == loginHistory.GetLoginType())
        {
            ui->tableWidget->setItem(nRow, 0, new QTableWidgetItem(QString(loginHistory.GetAccount().c_str())));
            ui->tableWidget->setItem(nRow, 1, new QTableWidgetItem(QString(loginHistory.GetIP().c_str())));
            ui->tableWidget->setItem(nRow, 2, new QTableWidgetItem(QString(loginHistory.GetPort().c_str())));
            ui->tableWidget->setItem(nRow, 3, new QTableWidgetItem(QString(loginHistory.GetBeginTime().c_str())));
            ui->tableWidget->setItem(nRow, 4, new QTableWidgetItem(QString(loginHistory.GetEndTime().c_str())));
            ui->tableWidget->setItem(nRow, 5, new QTableWidgetItem(QString(loginHistory.GetContinueTimeSec().c_str())));
            ui->tableWidget->setItem(nRow, 6, new QTableWidgetItem(QString(loginHistory.GetContinueTimeDay().c_str())));
            nRow++;
        }

    }
}

void UserManagerWidget::ReceiveAddUserData(UserModel userData)
{
    m_tableUserCache.insert(userData);
    UpdateTableUserData(0);

    qDebug() << "UserManagerWidget::ReceiveUserData>>m_tableCache.size" << m_tableUserCache.size();
}

void UserManagerWidget::ReceiveQueryUserData(set<UserModel> &setUserData)
{

    m_tableUserCache.insert(setUserData.begin(), setUserData.end());
    UpdateTableUserData(0);

    qDebug() << "UserManagerWidget::ReceiveUserData>>m_tableCache.size" << m_tableUserCache.size();
}

void UserManagerWidget::ReceiveLoginHistory(set<LoginHistoryModel> &setLoginHistory)
{
    m_tableLoginCache.insert(setLoginHistory.begin(), setLoginHistory.end());
    UpdateTableLoginHistory(0);

    qDebug() << "UserManagerWidget::ReceiveLoginHistory>>m_tableLoginCache.size" << m_tableLoginCache.size();
}

void UserManagerWidget::ReceiveSearchText(int nCmdOp, QString &strText)
{
    ui->tableWidget->clearContents();
    int currentRow = ui->listWidget->currentRow() == -1 ? 0 : ui->listWidget->currentRow();

    if (nCmdOp == OPERATE_QUERY_USER_DATA)
    {
        strText.isEmpty() ? UpdateTableUserData(currentRow) : SearchTableUserData(currentRow, strText);
    }
    else if (nCmdOp == OPERATE_QUERY_LOGIN_HISTORY)
    {
        strText.isEmpty() ? UpdateTableLoginHistory(currentRow) : SearchTableLoginHistory(currentRow, strText);
    }
}

void UserManagerWidget::UpdateTableLoginHistory(int currentRow)
{
    //清理tableWidget内容
    ui->tableWidget->clearContents();

    int nRow = 0;
    ui->tableWidget->setRowCount(m_tableLoginCache.size());
    set<LoginHistoryModel>::iterator iter = m_tableLoginCache.begin();
    for (; iter != m_tableLoginCache.end(); ++iter)
    {
        LoginHistoryModel loginHistory = *iter;
        if (loginHistory.GetLoginType() == currentRow)
        {
            ui->tableWidget->setItem(nRow, 0, new QTableWidgetItem(QString(loginHistory.GetAccount().c_str())));
            ui->tableWidget->setItem(nRow, 1, new QTableWidgetItem(QString(loginHistory.GetIP().c_str())));
            ui->tableWidget->setItem(nRow, 2, new QTableWidgetItem(QString(loginHistory.GetPort().c_str())));
            ui->tableWidget->setItem(nRow, 3, new QTableWidgetItem(QString(loginHistory.GetBeginTime().c_str())));
            ui->tableWidget->setItem(nRow, 4, new QTableWidgetItem(QString(loginHistory.GetEndTime().c_str())));
            ui->tableWidget->setItem(nRow, 5, new QTableWidgetItem(QString(loginHistory.GetContinueTimeSec().c_str())));
            ui->tableWidget->setItem(nRow, 6, new QTableWidgetItem(QString(loginHistory.GetContinueTimeDay().c_str())));
            nRow++;
        }
    }
}

void UserManagerWidget::DeleteItemAction()
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
    int currentRow = ui->tableWidget->currentRow();

    //删除缓存中的数据
    if (m_nOpType == OPERATE_QUERY_USER_DATA)
    {
        item = ui->tableWidget->item(currentRow, 4);
        qDebug() << "UserManagerWidget::DeleteTableItem" << item->text();
        set<UserModel>::iterator iter = m_tableUserCache.begin();
        for (;iter != m_tableUserCache.end();)
        {
            UserModel userdata = *iter;
            if (item->text() == QString(userdata.GetPhone().c_str()))
            {
                iter = m_tableUserCache.erase(iter);
                //删除用户数据操作发送到服务器
                emit this->SendDeleteUserData(userdata.GetUserID());
            }
            else
            {
                ++iter;
            }
        }



    }
    else if (m_nOpType == OPERATE_QUERY_LOGIN_HISTORY)
    {
        item = ui->tableWidget->item(currentRow, 0);
        qDebug() << "UserManagerWidget::DeleteTableItem" << item->text();
        set<LoginHistoryModel>::iterator iter = m_tableLoginCache.begin();
        for (;iter != m_tableLoginCache.end();)
        {
            LoginHistoryModel logindata = *iter;
            if (item->text() == QString(logindata.GetAccount().c_str()))
            {
                iter = m_tableLoginCache.erase(iter);
                //删除登录历史数据操作发送到服务器
                QString strAcount = logindata.GetAccount().c_str();
                emit this->SendDeleteLoginHistory(strAcount);
            }
            else
            {
                ++iter;
            }
        }
    }

    //删除控件中的数据
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void UserManagerWidget::AddUserTypeItemAction()
{
    QDialog *dlg = new QDialog(this, Qt::WindowCloseButtonHint);

    QLabel *label = new QLabel(dlg);
    label->setText("用户类型:");
    label->move(10, 10);

    QLineEdit *lineEdit = new QLineEdit(dlg);
    lineEdit->move(label->width() - 20, 10);

    QPushButton *btnOk = new QPushButton(dlg);
    btnOk->resize(75, 35);
    btnOk->move(25, 55);
    btnOk->setText("确定");
    QPushButton *btnBack = new QPushButton(dlg);
    btnBack->resize(75, 35);
    btnBack->move(140, 55);
    btnBack->setText("返回");



    //dlg->resize(240, 50);
    dlg->setWindowTitle("添加用户类型");
    dlg->setFixedSize(240, 100);
    dlg->show();

    connect(btnOk, &QPushButton::clicked, dlg, [=](){
        QString strText = lineEdit->text();
        ui->listWidget->addItem(strText);
        emit this->SendUserType(m_nListColumnCount + 1, strText);
        dlg->accept();
    });

    connect(btnBack, &QPushButton::clicked, dlg, [=](){
        dlg->reject();
    });
}

void UserManagerWidget::CopyRowItemAction()
{
    QString strText;
    int currentRow = ui->tableWidget->currentRow();
    for (int i = 0; i < m_nTableColumnCount; ++i)
    {
        QTableWidgetItem *item = ui->tableWidget->item(currentRow, i);
        strText += item->text() + " ";
    }

    QClipboard *clip = QApplication::clipboard();
    clip->setText(strText);
}

void UserManagerWidget::QueryDetailAction()
{
    QDialog *dlg = new QDialog(this);
    dlg->resize(300, 300);
    dlg->setWindowTitle("查看详细信息");

    QTextEdit *textEdit = new QTextEdit(dlg);
    textEdit->resize(300, 300);
    textEdit->setReadOnly(true);

    //获取单元格的数据，并显示到textEdit
    QString strText;
    int currentRow = ui->tableWidget->currentRow();
    QStringList::iterator iter = m_strTableHeader.begin();
    for (int i = 0; i < m_nTableColumnCount && iter != m_strTableHeader.end(); ++i, ++iter)
    {
        QTableWidgetItem *item = ui->tableWidget->item(currentRow, i);
        strText += (*iter) + ": " + item->text() + "\r\n";
    }

    textEdit->setText(strText);

    dlg->show();
    dlg->setAttribute(Qt::WA_DeleteOnClose); //55号 属性
}

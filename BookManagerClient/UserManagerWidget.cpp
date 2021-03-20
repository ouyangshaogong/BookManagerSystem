#include "UserManagerWidget.h"
#include "ui_UserManagerWidget.h"
#include <QDebug>

UserManagerWidget::UserManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagerWidget)
{
    ui->setupUi(this);

    //m_strOpTypList << QUERY_USER_DATA << QUERY_LOGIN_HISTORY;
    m_nCmdMapUpdateOpData[CMD_QUERY_USER_DATA] = &UserManagerWidget::UpdateTableUserData;
    //按比例布局控件
    LayoutWidget();

    //点击用户类型显示用户数据
    connect(ui->listWidget, &QListWidget::itemClicked, this, &UserManagerWidget::DisplayUserData);

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
    //设置列数
    ui->tableWidget->setColumnCount(strTableHeader.size());
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

void UserManagerWidget::DisplayUserData(QListWidgetItem *item)
{
    qDebug() << "UserManagerWidget::DisplayUserData>>";

    map<int, pUpdateOperateData>::iterator iter = m_nCmdMapUpdateOpData.find(m_nOpType);
    if (iter != m_nCmdMapUpdateOpData.end())
    {
        (this->*iter->second)(ui->listWidget->currentRow());
    }
}

void UserManagerWidget::UpdateTableUserData(int currentRow)
{
    //清理tableWidget内容
    ui->tableWidget->clearContents();

    int nRow = 0;
    ui->tableWidget->setRowCount(m_tableCache.size());
    set<UserModel>::iterator iter = m_tableCache.begin();
    for (; iter != m_tableCache.end(); ++iter)
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

void UserManagerWidget::ReceiveUserData(set<UserModel> setUserData)
{
    m_tableCache.insert(setUserData.begin(), setUserData.end());
    UpdateTableUserData(0);

    qDebug() << "UserManagerWidget::ReceiveUserData>>m_tableCache.size" << m_tableCache.size();
}

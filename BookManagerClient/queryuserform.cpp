#include "queryuserform.h"
#include "ui_queryuserform.h"
#include <QDebug>

QueryUserForm::QueryUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryUserForm)
{
    ui->setupUi(this);

    //按比例布局控件
    LayoutWidget();
    //设置空间头部
    SetWidgetHeader();

    connect(ui->listWidget, &QListWidget::itemClicked, this, &QueryUserForm::DisplayUserData);

    qDebug() << "QueryUserForm 构造了";
}

QueryUserForm::~QueryUserForm()
{
    qDebug() << "QueryUserForm 析构了";
    delete m_layout;
    delete ui;
}

void QueryUserForm::SetWidgetHeader()
{
    QStringList listHeader;
    listHeader << "管理员" << "普通读者" << "游客";
    ui->listWidget->addItems(listHeader);

    QStringList tableHeader;
    //设置列数
    ui->tableWidget->setColumnCount(5);
    //设置水平表头
    tableHeader.append("用户名");
    tableHeader.append("性别");
    tableHeader.append("生日");
    tableHeader.append("家庭地址");
    tableHeader.append("电话");
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void QueryUserForm::LayoutWidget()
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

void QueryUserForm::DisplayUserData(QListWidgetItem *item)
{

    UpdateTableUserData(ui->listWidget->currentRow());
    qDebug() << "QueryUserForm::DisplayUserData>>";
}

void QueryUserForm::UpdateTableUserData(int currentRow)
{
    int nRow = 0;
    ui->tableWidget->setRowCount(m_tableCache.size());
    set<UserModel>::iterator iter = m_tableCache.begin();
    for (; iter != m_tableCache.end(); ++iter)
    {
        UserModel userdata = *iter;
        if (userdata.GetUserType() == currentRow)
        {
            ui->tableWidget->setItem(nRow, 0, new QTableWidgetItem(QString(userdata.GetUserName().c_str())));
            qDebug() << userdata.GetUserName().c_str() << QString::number(ui->listWidget->currentRow());
            ui->tableWidget->setItem(nRow, 1, new QTableWidgetItem(QString(userdata.GetSex().c_str())));
            ui->tableWidget->setItem(nRow, 2, new QTableWidgetItem(QString(userdata.GetBirth().c_str())));
            ui->tableWidget->setItem(nRow, 3, new QTableWidgetItem(QString(userdata.GetAddress().c_str())));
            ui->tableWidget->setItem(nRow, 4, new QTableWidgetItem(QString(userdata.GetPhone().c_str())));
            nRow++;
        }
    }
}

void QueryUserForm::ReceiveUserData(set<UserModel> setUserData)
{

    m_tableCache.insert(setUserData.begin(), setUserData.end());

    UpdateTableUserData(0);
    qDebug() << "QueryUserForm::ReceiveUserData>>m_tableCache.size" << m_tableCache.size();
}

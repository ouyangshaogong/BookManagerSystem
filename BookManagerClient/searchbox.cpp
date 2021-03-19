#include "searchbox.h"
#include "ui_searchbox.h"
#include <QSizePolicy>
#include <QIcon>
#include <QDebug>

SearchBox::SearchBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchBox)
{
    ui->setupUi(this);

    m_hBoxLayout = new QHBoxLayout;      // 新建水平布局管理器
    m_hBoxLayout->addWidget(ui->lineEdit);        // 向布局管理器中添加部件
    m_hBoxLayout->addWidget(ui->pushButton);

    // 设置部件间的间隔
    m_hBoxLayout->setSpacing(5);
    // 按比例设置控件位置
    //m_hBoxLayout->setStretch(0, 4);
    //m_hBoxLayout->setStretch(1, 1);
    setLayout(m_hBoxLayout);

    //添加图片资源
    QIcon icon(":/Images/search.png");
    ui->pushButton->setIcon(icon);

    connect(ui->pushButton, &QPushButton::clicked, this, &SearchBox::GetLineEditText);
}

SearchBox::~SearchBox()
{
    delete ui;
}

void SearchBox::GetLineEditText()
{
    qDebug() << "SearchBox::GetLineEditText";
    QString strText = ui->lineEdit->text();
    emit this->SendLineEditText(strText);
    ui->lineEdit->clear();
}

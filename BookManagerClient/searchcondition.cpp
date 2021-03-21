#include "searchcondition.h"
#include "ui_searchcondition.h"

SearchCondition::SearchCondition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchCondition)
{
    ui->setupUi(this);

    m_hBoxLayout = new QHBoxLayout;      // 新建水平布局管理器
    m_hBoxLayout->addWidget(ui->labelCond);        // 向布局管理器中添加部件
    m_hBoxLayout->addWidget(ui->comboBoxCond);

    // 设置部件间的间隔
    m_hBoxLayout->setSpacing(5);
    // 按比例设置控件位置
    //m_hBoxLayout->setStretch(0, 4);
    //m_hBoxLayout->setStretch(1, 1);
    setLayout(m_hBoxLayout);
}

SearchCondition::~SearchCondition()
{
    delete ui;
}


void SearchCondition::setLabelText(QString strText)
{
    ui->labelCond->setText(strText);
}

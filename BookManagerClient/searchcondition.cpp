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
    setLayout(m_hBoxLayout);

    //QComboBox 组件上选择项发生变化时，获取数据
    connect(ui->comboBoxCond, &QComboBox::currentTextChanged, this, &SearchCondition::ReceiveComboBoxText);
}

SearchCondition::~SearchCondition()
{
    delete ui;
}


void SearchCondition::setLabelText(QString strText)
{
    ui->labelCond->setText(strText);
}

void SearchCondition::setDefaultComboText(int index)
{
    ui->comboBoxCond->setCurrentIndex(index);
}

void SearchCondition::GetComboBoxText(QStringList &strTextList)
{
    ui->comboBoxCond->addItems(strTextList);
}

void SearchCondition::ReceiveComboBoxText(const QString &strText)
{
    emit SendComboBoxText(strText);
}

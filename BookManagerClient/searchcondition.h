#ifndef SEARCHCONDITION_H
#define SEARCHCONDITION_H

#include <QWidget>
#include <QHBoxLayout>


namespace Ui {
class SearchCondition;
}

class SearchCondition : public QWidget
{
    Q_OBJECT

public:
    explicit SearchCondition(QWidget *parent = nullptr);
    ~SearchCondition();

    void setLabelText(QString strText);
    void setDefaultComboText(int index);

signals:
    void SendComboBoxText(QString strText);
public slots:
    void GetComboBoxText(QStringList &strTextList);
    void ReceiveComboBoxText(const QString &strText);
private:
    Ui::SearchCondition *ui;

    QHBoxLayout *m_hBoxLayout;
};

#endif // SEARCHCONDITION_H

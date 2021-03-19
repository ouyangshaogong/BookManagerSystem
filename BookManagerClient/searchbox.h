#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QWidget>
#include <QHBoxLayout>

namespace Ui {
class SearchBox;
}

class SearchBox : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBox(QWidget *parent = nullptr);
    ~SearchBox();

signals:
    void SendLineEditText(QString strText);
public slots:
    void GetLineEditText();
private:
    Ui::SearchBox *ui;

    QHBoxLayout *m_hBoxLayout;
};

#endif // SEARCHBOX_H

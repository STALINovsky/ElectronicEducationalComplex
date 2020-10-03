#ifndef TESTWIDGETITEM_H
#define TESTWIDGETITEM_H

#include <QWidget>

namespace Ui {
class TestWidgetItem;
}

class TestWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidgetItem(QWidget *parent = nullptr);
    ~TestWidgetItem();

    void setSearchPath(QString path);
    void setSource(QString path);
public slots:
    void freezeButtons();
private slots:
    void onAnswerButton();
signals:
    void answerChanged(QString newAnswer);

    void BackButtonClicked();
    void nextButtonClicked();


private:
    Ui::TestWidgetItem *ui;
};

#endif // TESTWIDGETITEM_H

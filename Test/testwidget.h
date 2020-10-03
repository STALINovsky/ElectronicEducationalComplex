#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QTabWidget>
#include <QFile>
#include <QDir>
#include <QtDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QHeaderView>
#include "testwidgetitem.h"

namespace Ui {
class TestWidget;
}

class TestWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QString path,QWidget *parent = nullptr);
    ~TestWidget();

signals:
    void finished(QString answers);
    void closed(QString testName);

private:
    Ui::TestWidget *ui;

    QString testName;
    QVector<QString> answers;
    bool isAnswersSended = 0;


    void InsertTestItem(QString TestPath,int index);
    void closeEvent(QCloseEvent *event) override;
    bool isAllQuestionsAnswered();
    bool confirmAction(QString Message);

private slots:
    void onBackButtonClicked();
    void onNextButtonClicked();

    void newAnswer(QString newAnsver);
    void sendAnswers();

    void showDecision(QString decision);


};

#endif // TESTWIDGET_H

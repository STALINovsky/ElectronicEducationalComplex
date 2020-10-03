#include "testwidgetitem.h"
#include "ui_testwidgetitem.h"

TestWidgetItem::TestWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidgetItem)
{
    ui->setupUi(this);

    connect(ui->A_Button,SIGNAL(clicked()),this,SLOT(onAnswerButton()));
    connect(ui->B_Button,SIGNAL(clicked()),this,SLOT(onAnswerButton()));
    connect(ui->C_Button,SIGNAL(clicked()),this,SLOT(onAnswerButton()));
    connect(ui->D_button,SIGNAL(clicked()),this,SLOT(onAnswerButton()));
    connect(ui->E_button,SIGNAL(clicked()),this,SLOT(onAnswerButton()));

    connect(ui->backButton,SIGNAL(clicked()),this,SIGNAL(BackButtonClicked()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SIGNAL(nextButtonClicked()));
}

TestWidgetItem::~TestWidgetItem()
{
    delete ui;
}

void TestWidgetItem::setSearchPath(QString path)
{
    QStringList pathList;
    pathList << path;
    ui->contentBrowser->setSearchPaths(pathList);
}

void TestWidgetItem::setSource(QString path)
{
    ui->contentBrowser->setSource(path);
}

void TestWidgetItem::freezeButtons()
{
    ui->A_Button->setEnabled(false);
    ui->B_Button->setEnabled(false);
    ui->C_Button->setEnabled(false);
    ui->D_button->setEnabled(false);
    ui->E_button->setEnabled(false);
}

void TestWidgetItem::onAnswerButton()
{
    void* senderButton = sender();
    if(senderButton == ui->A_Button)
    {
        emit answerChanged("A");
    }
    else if (senderButton == ui->B_Button) {
        emit answerChanged("B");
    }
    else if (senderButton == ui->C_Button) {
        emit answerChanged("C");
    }
    else if (senderButton == ui->D_button) {
        emit answerChanged("D");
    }
    else if (senderButton == ui->E_button) {
        emit answerChanged("E");
    }
}


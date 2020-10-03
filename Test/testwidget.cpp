#include "testwidget.h"
#include "ui_testwidget.h"

TestWidget::TestWidget(QString path,QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(sendAnswers()));
    connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(onNextButtonClicked()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(onBackButtonClicked()));

    QString AboutTestSource = path + "/" + "AboutTest" + "/" + "AboutTest.htm";
    QStringList AboutTestSearch {(path + "/" + "AboutTest" + "/" + "AboutTest.files")};
    ui->aboutTestBrowser->setSource(AboutTestSource);
    ui->aboutTestBrowser->setSearchPaths(AboutTestSearch);

    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    testName = dir.dirName();
    QStringList infoList = dir.entryList().filter(QRegExp("(TestItem)"));

    for (int i = 0; i < infoList.length();i++) {
        this->InsertTestItem(path + "/" +infoList[i], i + 1);
    }
    answers.resize(infoList.length());
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::InsertTestItem(QString TestPath,int TestItemIndex)
{
    ui->decisionWidget->appendQuestion();

    QDir dir(TestPath);
    dir.setFilter(QDir::NoDot | QDir::NoDotDot);
    QStringList infoList = dir.entryList();

    TestWidgetItem* newItem = new TestWidgetItem(this);

    QString searchPath = TestPath + "/" + dir.dirName() + ".files" ;
    QString sourcePath = TestPath + "/" + dir.dirName() + ".htm";

    newItem->setSearchPath(searchPath);
    newItem->setSource(sourcePath);
    newItem->BackButtonClicked();

    connect(newItem,SIGNAL(nextButtonClicked()),this,SLOT(onNextButtonClicked()));
    connect(newItem,SIGNAL(BackButtonClicked()),this,SLOT(onBackButtonClicked()));
    connect(newItem,SIGNAL(answerChanged(QString)),this,SLOT(newAnswer(QString)));
    connect(this,SIGNAL(finished(QString)),newItem,SLOT(freezeButtons()));


    QString tabName = tr("Вопрос %1");
    tabName = tabName.arg(TestItemIndex);
    this->insertTab(TestItemIndex,newItem,tabName);
}

void TestWidget::closeEvent(QCloseEvent *event)
{
    QString Message ;
    if(isAnswersSended && isAllQuestionsAnswered())
    {
        Message = tr("Вы действительно хотите выйти?");
    }
    else {
        Message = tr("Вы действительно хотите выйти?\n(Некоторые вопросы не отвечены!)");
    }

    if(confirmAction(Message)){
        event->accept();
        emit closed(this->testName);
        if(!isAnswersSended)
        {
            sendAnswers();
        }
        this->deleteLater();
    }
    else
    {
        event->ignore();
    }

}

bool TestWidget::isAllQuestionsAnswered()
{
    return !this->answers.contains("");
}

bool TestWidget::confirmAction(QString message)
{
    QMessageBox* confirmer = new QMessageBox(QMessageBox::Icon::Question,tr("Подтвердите действие"), message);

    QPushButton* yesButton = new QPushButton(tr("Да"),confirmer);
    QPushButton* noButton = new QPushButton(tr("Нет"),confirmer);
    confirmer->addButton(yesButton,QMessageBox::ButtonRole::YesRole);
    confirmer->addButton(noButton,QMessageBox::ButtonRole::NoRole);

    confirmer->setModal(true);
    confirmer->exec();
    bool result  = confirmer->clickedButton() == yesButton;
    delete confirmer;

    return  result;
}

void TestWidget::showDecision(QString decision)
{
    QStringList decisionList = decision.split('\n');
    ui->decisionWidget->setDecisions(decisionList);
}

void TestWidget::onBackButtonClicked()
{
    int currentIndex = this->currentIndex();
    this->setCurrentIndex(currentIndex + 1);
}

void TestWidget::onNextButtonClicked()
{
    int currentIndex = this->currentIndex();
    this->setCurrentIndex(currentIndex - 1);
}

void TestWidget::newAnswer(QString newAnswer)
{
    int curruntIndex = this->currentIndex();
    answers[curruntIndex - 1] = newAnswer;
    ui->decisionWidget->setAnswer(curruntIndex - 1,newAnswer);
}

void TestWidget::sendAnswers()
{   
    QChar separator = '\n';
    QString answersString = QStringList::fromVector(answers).join(separator);
    QStringList userData;

    userData
    << testName
    << ui->surnameEdit->text()//surname
    << ui->nameEdit->text()//name
    << ui->groupEdit->text()//group
    <<  answersString;//answers

    emit finished(userData.join(separator));
    isAnswersSended = true;
    ui->sendButton->setEnabled(false);
}

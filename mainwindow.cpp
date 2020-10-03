#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeLections->load_data("Lessions");
    connect(ui->treeLections,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(set_content(QTreeWidgetItem*,int)));
    connect(ui->treeLabs,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(set_content(QTreeWidgetItem*,int)));

    loader = new DataLoader();
    loader->moveToThread(&loaderThread);
    connect(this,SIGNAL(connectToServer(QString,int)),loader,SLOT(connectToServer(QString,int)));
    connect(loader,SIGNAL(connectionSuccessful()),this,SLOT(refreshData()));
    loaderThread.start();
    emit this->connectToServer("127.0.0.1",80);

    connect(ui->treeTests,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(startTest(QTreeWidgetItem*,int)));
}

MainWindow::~MainWindow()
{
    this->loaderThread.quit();
    this->loaderThread.wait();
    delete ui;
}

void MainWindow::refreshData()
{
    // request siganls
    connect(this,SIGNAL(loadTestList()),loader,SLOT(loadTestList()));
    connect(this,SIGNAL(loadTest(QString)),loader,SLOT(loadTest(QString)));
    connect(this,SIGNAL(loadLectures()),loader,SLOT(refreshLectures()));
    connect(this,SIGNAL(loadLabs()),loader,SLOT(refreshLabs()));

    connect(loader,SIGNAL(testListLoaded(QStringList)),this,SLOT(refreshTestList(QStringList)));
    connect(loader,SIGNAL(labsLoaded()),this,SLOT(refreshLabsList()));
    connect(loader,SIGNAL(lecturesLoaded()),this,SLOT(refreshLessionsList()));

    emit this->loadTestList();
    emit this->loadLabs();
    emit this->loadLectures();
}

void MainWindow::set_content(QTreeWidgetItem *item,int column)
{
    QStringList data = item->data(column,Qt::ItemDataRole::UserRole).toStringList();
    QStringList searchPath {data.at(0)};
    QString SourcePath = data.at(1);

    ui->contentBrowser->setSearchPaths(searchPath);
    ui->contentBrowser->setSource(SourcePath);
}

void MainWindow::refreshTestList(QStringList testList)
{
    QTreeWidget* treeTest = ui->treeTests;
    treeTest->clear();
    foreach(QString testName,testList)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0,testName);
        QString pathToTest = "Tests/" + testName;
        item->setData(0,Qt::ItemDataRole::UserRole,pathToTest);
        treeTest->addTopLevelItem(item);
    }
}

void MainWindow::refreshLessionsList()
{
    ui->treeLections->clear();
    ui->treeLections->load_data("Lessions");
}

void MainWindow::refreshLabsList()
{
    ui->treeLabs->clear();
    ui->treeLabs->load_data("Labs");
}


void MainWindow::startTest(QTreeWidgetItem* item,int column)
{
    this->hide();
    QStringList data = item->data(column,Qt::ItemDataRole::UserRole).toStringList();
    QString searchPath  = data.at(0);
    emit this->loadTest(searchPath.split('/').last());

    QProgressDialog* progress = new QProgressDialog(tr("Пожалуйста подождите"),tr("Закрыть"),0,100);
    connect(loader,SIGNAL(loadProgress(int)),progress,SLOT(setValue(int)));
    connect(loader,SIGNAL(testLoaded(QString)),progress,SLOT(close()));
    progress->setModal(true);
    progress->show();
    progress->exec();
    delete  progress;
    
    test = new TestWidget (searchPath);
    connect(test,SIGNAL(finished(QString)),loader,SLOT(loadDecision(QString)));
    connect(test,SIGNAL(closed(QString)),this,SLOT(testClosed(QString)));
    connect(loader,SIGNAL(decisionLoaded(QString)),test,SLOT(showDecision(QString)));
    test->show();
}

void MainWindow::testClosed(QString testName)
{
    QDir testDir("Tests/" + testName);
    testDir.removeRecursively();
    this->show();
}





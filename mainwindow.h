#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QtWidgets>
#include <QTextBrowser>
#include <QVector>
#include "dataLoader/datathread.h"
#include "Test/testwidget.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void connectToServer(QString host,int port);
    void loadTestList();
    void loadTest(QString testName);
    void loadLectures();
    void loadLabs();

private:
    QThread loaderThread;
    Ui::MainWindow *ui;
    DataLoader* loader;
    TestWidget* test;

    void trees_data_initialization(QTreeWidget* wgt,QString source_path);
private slots:
    void refreshData();
    void refreshTestList(QStringList testList);
    void refreshLessionsList();
    void refreshLabsList();

    void set_content(QTreeWidgetItem *item,int column);
    void startTest(QTreeWidgetItem*,int);
    void testClosed(QString testName);
};
#endif // MAINWINDOW_H

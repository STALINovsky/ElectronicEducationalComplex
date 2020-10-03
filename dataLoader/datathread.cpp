#include "datathread.h"

DataLoader::DataLoader():ClientSocket()
{
    connect(this,SIGNAL(destroyed()),this,SLOT(deleteLater()));
}


void DataLoader::loadTestList()
{
    if(socket->state() != QTcpSocket::SocketState::ConnectedState)
        return;
    qDebug() << QThread::currentThreadId();
    sendCommandToServer("Get test list");
    socket->waitForReadyRead();
    QStringList result = readCommandAndMessage();
    QString command = result[0];
    QString testsNames = result[1];
    qDebug() << command;
    qDebug() << result;

    QStringList testList = testsNames.split('\n');
    emit this->testListLoaded(testList);
}

void DataLoader::loadTest(QString testName)
{
    if(socket->state() != QTcpSocket::SocketState::ConnectedState)
        return;
    sendCommandToServer("Get test\n" + testName);
    socket->waitForReadyRead();
    QString command = readCommand();
    loadFiles();
    qDebug() << "Test " << testName << " loaded";
    emit this->testLoaded(testName);
}

void DataLoader::refreshLectures()
{
    if(socket->state() != QTcpSocket::SocketState::ConnectedState)
        return;
    sendCommandToServer("Get lessions");
    socket->waitForReadyRead();
    QString command = readCommand();
    loadFiles();
    qDebug() << "Lessions refreshed";
    emit this->lecturesLoaded();
}

void DataLoader::refreshLabs()
{
    if(socket->state() != QTcpSocket::SocketState::ConnectedState)
        return;
    sendCommandToServer("Get labs");
    socket->waitForReadyRead();
    QString command = readCommand();
    loadFiles();
    qDebug() << "Labs refreshed";
    emit this->labsLoaded();
}

void DataLoader::loadDecision(QString answerData)
{
    if(socket->state() != QTcpSocket::SocketState::ConnectedState)
        return;
    sendMessageToServer("Set answer",answerData);
    socket->waitForReadyRead();
    QStringList result = readCommandAndMessage();
    QString command = result[0];
    QString decisionData = result[1];
    qDebug() <<"Command:" << command << " I get decision";
    emit this->decisionLoaded(decisionData);
}


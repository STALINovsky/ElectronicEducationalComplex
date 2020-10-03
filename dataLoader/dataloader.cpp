#include "dataloader.h"

ClientSocket::ClientSocket(QObject *parent) : QObject(parent)
{

}
void ClientSocket::connectToServer(QString host, int port)
{
    this->host = host;
    this->port = port;
    socket = new QTcpSocket(this);
    socket->connectToHost(host,port);
    socket->waitForConnected();
    if(socket->state() != QTcpSocket::ConnectedState)
    {
        return;
    }
    connect(socket, SIGNAL(connected()),this, SLOT(onConnected()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()),Qt::DirectConnection);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)),Qt::DirectConnection);
    emit this->connectionSuccessful();

}

void ClientSocket::disconnectFromServer()
{
    socket->disconnectFromHost();
}

void ClientSocket::onConnected()
{
    qDebug() << "Server has been connected!";
}

QString ClientSocket::readCommand()
{
    qDebug() << socket->bytesAvailable();
    QDataStream in(socket);
    int messageSize;
    in >> messageSize;

    while (socket->bytesAvailable() < messageSize)
        socket->waitForReadyRead();
    QString command;
    in >> command;
    qDebug() << "I got a command" << command;
    return command;
}

QStringList ClientSocket::readCommandAndMessage()
{
    qDebug() << socket->bytesAvailable();
    QDataStream in(socket);
    int messageSize;
    in >> messageSize;
    while (socket->bytesAvailable() < messageSize)
        socket->waitForReadyRead();
    QString command;
    QString message;

    in >> command;
    in >> message;
    qDebug() << "I got a command" << command << "and message" << message;
    return QStringList{command,message};
}

void ClientSocket::sendCommandToServer(QString command)
{
    QDataStream out(socket);
    int commnadSize = (command.size() + 1) * 2;
    qDebug() <<"Sending comand: " << command;
    out << commnadSize << command;
    socket->waitForBytesWritten();
}

void ClientSocket::sendMessageToServer(QString comand,QString message)
{
    QDataStream out(socket);
    int messageSize = (message.size() + comand.size() +2)*2;
    qDebug() <<"Sending message" << "comand: " << comand  << "message: " << message;
    out << messageSize << comand << message;
}

void ClientSocket::loadFiles()
{
    QDataStream in(socket);
    int filesCount;
    in >> filesCount;
    for (int i = 0; i < filesCount && (socket->bytesAvailable() >= 4 or socket->waitForReadyRead()) ;i++) {
        loadFile();
        int procent = 100*((double) i / filesCount);
        emit this->loadProgress(procent);
    }
}

void ClientSocket::onDisconnected()
{
    //Закрытие сокета
    socket->close();
}

void ClientSocket::onError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found."
                                  : err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed."
                                  : err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused."
                                  : QString(socket->errorString()) );
    qDebug() << strError;

}

void ClientSocket::loadFile()
{
    QDataStream in(socket);

    int metaDataSize;
    QByteArray serverHash;
    QString name;
    in  >> metaDataSize;
    while(socket->bytesAvailable() < metaDataSize)
         socket->waitForReadyRead();

    in >> serverHash >> name;
    QFile file (name);
    QByteArray myHash;
    myHash.resize(128);
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        myHash = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5);
        qDebug() << myHash;
        file.close();
    }

    QDataStream out(socket);
    out << myHash;
    if(serverHash != myHash)
    {
        int fileSize;
        while(4 > socket->bytesAvailable())
            socket->waitForReadyRead();
        in >> fileSize;

        qDebug() << "SIZE :" << fileSize << "Name " << name;
        add_dirs(name);

        while(socket->bytesAvailable() < fileSize)
             socket->waitForReadyRead();

        file.open(QIODevice :: WriteOnly);
        file.write(socket->read(fileSize));
        file.close();
    }
    else {
        qDebug() << "File was downloaded";
    }
}

void ClientSocket::add_dirs(QString filePath)
{
    QStringList dirs = filePath.split("/");
    QDir dir;
    QString dirPath = dirs[0];
    dir.mkdir(dirPath);
    for (auto it = dirs.begin() +1;it != dirs.end() - 1;++it) {
        dirPath += "/" + *it;
        dir.mkdir(dirPath);
    }
}



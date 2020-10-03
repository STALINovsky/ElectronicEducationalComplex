#ifndef TESTLOADER_H
#define TESTLOADER_H

#include <QThread>
#include <QTcpSocket>
#include <QDataStream>
#include <QCryptographicHash>
#include <QThread>
#include <QFile>
#include <QDir>
#include <QBuffer>


class ClientSocket : public QObject
{
    Q_OBJECT
signals:
    void connectionSuccessful();
    void loadProgress(int percent);
public:
    explicit ClientSocket(QObject *parent = nullptr);
    QString readCommand();
    QStringList readCommandAndMessage();
    void loadFiles();
    void sendCommandToServer(QString command);
    void sendMessageToServer(QString comand,QString message);

public slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);
    void connectToServer(QString host,int port);
    void disconnectFromServer();

private:
    void loadFile();
protected:
    QString host;
    int port;
    QTcpSocket* socket;
    void add_dirs(QString filePath);
};

#endif // TESTLOADER_H

#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "ChatProtocol.h"

#include <QObject>
#include <QTcpSocket>

class ClientManager : public QObject
{
    Q_OBJECT
public:
     explicit ClientManager(const QHostAddress &ip = QHostAddress("192.168.100.101"), ushort port = 4500, QObject *parent = nullptr);

    void connectToServer();

    void sendMessage(QString message, QString receiver);
    void sendName(QString name);
    void sendStatus(ChatProtocol::Status status);
    void sendIsTyping();

signals:
    void connected();
    void disconnected();
//    void dataReceived(QByteArray data);
    void textMessageReceived(QString message);
    void isTyping();
    void nameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);

    void connectionACK(QString myName, QStringList clientsName);
    void newClientConnectedToServer(QString clienName);
    void clientNameChanged(QString prevName, QString clientName);
    void clientDisconnected(QString clientName);

private slots:
    void readyRead();

private: //fields
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;
private: //methods
     void setupClient();
};

#endif // CLIENTMANAGER_H

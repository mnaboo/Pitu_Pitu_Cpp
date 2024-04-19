#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QByteArray>
#include <QString>

class ChatProtocol
{
public:
    enum MessageType{
        Text,
        IsTyping,
        SetName,
        SetStatus,
        ClientName,
        connectionACK,
        NewClient,
        ClientDisconnected
    };
    enum Status{
        None,
        Available,
        Away,
        Busy
    };

    ChatProtocol();

    QByteArray textMessage(QString message, QString receiver);
    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString name);
    QByteArray setStatusMessage(Status status);

    QByteArray setClientNameMessage(QString prevName, QString name);
    QByteArray setConnectionACKMessage(QString clientName, QStringList otherClients);
    QByteArray setNewClientMessage(QString clientName);
    QByteArray setClientDisconnectedMessage (QString clientName);

    void loadData(QByteArray data);

    QString message() const;

    QString name() const;

    Status status() const;

    MessageType type() const;

    QString receiver() const;

private:
    QByteArray getData(MessageType type, QString data);

    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
    QString _receiver;
};

#endif // CHATPROTOCOL_H

#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QByteArray>
#include <QString>
#include <QStringList>


class ChatProtocol
{
public:
    enum MessageType{
        Text,
        IsTyping,
        SetName,
        SetStatus,
        ClientName,
        ConnectionACK,
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
    QByteArray isTypingMessage(QString receiver);
    QByteArray setNameMessage(QString name);
    QByteArray setStatusMessage(Status status);

    void loadData(QByteArray data);

    const QString &message() const;

    const QString &name() const;

    Status status() const;

    MessageType type() const;

    QString receiver() const;

    const QString &clientName() const;

    const QString &prevName() const;

    const QStringList &clientsName() const;

    const QString &myName() const;

private:
    QByteArray getData(MessageType type, QString data);

    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
    QString _receiver;
    QString _clientName;
    QString _prevName;
    QStringList _clientsName;
    QString _myName;

};

#endif // CHATPROTOCOL_H

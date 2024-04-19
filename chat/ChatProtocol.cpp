#include "ChatProtocol.h"
#include <QIODevice>

ChatProtocol::ChatProtocol()
{

}

QByteArray ChatProtocol::setClientNameMessage(QString prevName, QString name)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << ClientName << prevName << name;
    return ba;
}

QByteArray ChatProtocol::setConnectionACKMessage(QString clientName, QStringList otherClients)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << connectionACK << clientName << otherClients;
    return ba;
}

QByteArray ChatProtocol::setNewClientMessage(QString clientName)
{
    return getData(NewClient, clientName);
}

QByteArray ChatProtocol::setClientDisconnectedMessage (QString clientName)
{
    return getData(ClientDisconnected, clientName);
}

QByteArray ChatProtocol::textMessage(QString message, QString receiver)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << ClientName << receiver << message;
    return ba;
}

QByteArray ChatProtocol::isTypingMessage()
{
    return getData(IsTyping, "");
}

QByteArray ChatProtocol::setNameMessage(QString name)
{
    return getData(SetName, name);
}

QByteArray ChatProtocol::setStatusMessage(Status status)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << SetStatus << status;

    return ba;
}

void ChatProtocol::loadData(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in >> _type;
    switch (_type) {
    case Text:
        in >> _receiver >> _message;
        break;
    case SetName:
        in >> _name;
        break;
    case SetStatus:
        in >> _status;
        break;
    default:
        break;
    }
}

QByteArray ChatProtocol::getData(MessageType type, QString data)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << type << data;

    return ba;
}

QString ChatProtocol::receiver() const
{
    return _receiver;
}

ChatProtocol::MessageType ChatProtocol::type() const
{
    return _type;
}

ChatProtocol::Status ChatProtocol::status() const
{
    return _status;
}

QString ChatProtocol::name() const
{
    return _name;
}

QString ChatProtocol::message() const
{
    return _message;
}

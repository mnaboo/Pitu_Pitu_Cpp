#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include "ClientManager.h"
#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *client, QWidget *parent = nullptr);
    void disconnect();
    ~ClientChatWidget();

private slots:
    void on_btnSend_clicked();
    void clientDisconnected();
    void textMessageReceived(QString message, QString receiver);
    void onTyping();
    void onClientNameChanged(QString prevname, QString name);

signals:
    void clientNameChanged(QString prevName, QString name);
    void isTyping(QString message);
    void statusChanged(ChatProtocol::Status status);
    void textForOtherClients(QString message, QString receiver, QString sender);
private:
    Ui::ClientChatWidget *ui;
    ClientManager *_client;
};

#endif // CLIENTCHATWIDGET_H

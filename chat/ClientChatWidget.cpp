#include "ClientChatWidget.h"
#include "ui_ClientChatWidget.h"

#include <QMessageBox>
#include <QDesktopServices>

ClientChatWidget::ClientChatWidget(QTcpSocket *client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientChatWidget)
{
    ui->setupUi(this);
    _client = new ClientManager(client, this);
//    connect(_client, &QTcpSocket::readyRead, this, &ClientChatWidget::dataReceived);
    connect(_client, &ClientManager::disconnected, this, &ClientChatWidget::clientDisconnected);
    connect(_client, &ClientManager::textMessageReceived, this, &ClientChatWidget::textMessageReceived);
    connect(_client, &ClientManager::isTyping, this, &ClientChatWidget::onTyping);
    connect(_client, &ClientManager::nameChanged, this, &ClientChatWidget::onClientNameChanged);
    connect(_client, &ClientManager::statusChanged, this, &ClientChatWidget::statusChanged);
    connect(ui->lnMessage, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);

    dir.mkdir(_client->name());
    dir.setPath("./" + _client->name());
}

void ClientChatWidget::disconnect()
{
    _client->disconnectFromHost();
}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}

void ClientChatWidget::clientDisconnected()
{
    ui->wdgSend->setEnabled(false);
}

void ClientChatWidget::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage("Server: " + message);
    ui->lnMessage->setText("");
    ui->listMessages->addItem("You: " + message);
}

void ClientChatWidget::textMessageReceived(QString message, QString receiver)
{
    if (receiver == "Server" || receiver == "All") {
        ui->listMessages->addItem(QString("%1: ").arg(_client->name()) + message);
    }
    if(receiver != "Server"){
        emit textForOtherClients(message, receiver, _client->name());
    }
}

void ClientChatWidget::onTyping()
{
    emit isTyping(QString("%1 is typing...").arg(_client->name()));
}

void ClientChatWidget::onClientNameChanged(QString prevName, QString name)
{
    QFile::rename(dir.canonicalPath(), name);
    emit clientNameChanged(prevName, name);
}


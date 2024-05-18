#include "ChatItemWidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupClient();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupClient()
{
    _client = new ClientManager();
    connect(_client , &ClientManager::connected, [this](){
        ui->centralwidget->setEnabled(true);
    });
    connect(_client, &ClientManager::disconnected, [this](){
        ui->centralwidget->setEnabled(false);
    });
    connect(_client, &ClientManager::textMessageReceived, this, &MainWindow::dataReceived);
    connect(_client, &ClientManager::isTyping, this, &MainWindow::onTyping);
    connect(ui->lnMessage, &QLineEdit::textChanged, this, [this]() {
        _client->sendIsTyping(ui->cmbDestination->currentText());
    });
    connect(_client, &ClientManager::connectionACK, this, &MainWindow::onConnectionACK);
    connect(_client, &ClientManager::newClientConnectedToServer, this, &MainWindow::onNewClientConnectedToServer);
    connect(_client, &ClientManager::clientDisconnected, this, &MainWindow::onClientDisconnected);
    connect(_client, &ClientManager::clientNameChanged, this, &MainWindow::onClientNameChanged);
}

void MainWindow::on_actionConnect_triggered()
{
    _client->connectToServer();
}


void MainWindow::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage(message, ui->cmbDestination->currentText());
//    ui->lstMessages->addItem(message);
    ui->lnMessage->setText("");
    ui->lnMessage->setFocus();

    auto chatWidget = new ChatItemWidget();
    chatWidget->setMessage("You: " + message, true);
    auto listWidgetItem = new QListWidgetItem();
    listWidgetItem->setSizeHint(QSize(0, 65));
    ui->listMessages->addItem(listWidgetItem);
    ui->listMessages->setItemWidget(listWidgetItem, chatWidget);
}

void MainWindow::dataReceived(QString message)
{
//    ui->lstMessages->addItem(data);
    auto chatWidget = new ChatItemWidget();
    chatWidget->setMessage(message);
    auto listWidgetItem = new QListWidgetItem();
    listWidgetItem->setSizeHint(QSize(0, 65));
    ui->listMessages->addItem(listWidgetItem);
    listWidgetItem->setBackground(QColor(82, 82, 82));
    ui->listMessages->setItemWidget(listWidgetItem, chatWidget);


}




void MainWindow::on_lnClientName_editingFinished()
{
    auto name = ui->lnClientName->text().trimmed();
    _client->sendName(name);
}


void MainWindow::on_cmbStatus_currentIndexChanged(int index)
{
    auto status = (ChatProtocol::Status)index;
    _client->sendStatus(status);
}

void MainWindow::onTyping(QString typing)
{
    statusBar()->showMessage(typing + " is typing...", 1000);
}

void MainWindow::onConnectionACK(QString myName, QStringList clientsName)
{
    ui->cmbDestination->clear();
    clientsName.prepend("All");
    clientsName.prepend("Server");
    foreach (auto client, clientsName) {
        ui->cmbDestination->addItem(client);
    }
    setWindowTitle(myName);
}

void MainWindow::onNewClientConnectedToServer(QString clienName)
{
    ui->cmbDestination->addItem(clienName);
}

void MainWindow::onClientNameChanged(QString prevName, QString clientName)
{
    for (int i = 0; i < ui->cmbDestination->count(); ++i) {
        if (ui->cmbDestination->itemText(i) == prevName) {
            ui->cmbDestination->setItemText(i, clientName);
            return;
        }
    }
}

void MainWindow::onClientDisconnected(QString clientName)
{
    for (int i = 0; i < ui->cmbDestination->count(); ++i) {
        if (ui->cmbDestination->itemText(i) == clientName) {
            ui->cmbDestination->removeItem(i);
            return;
        }
    }
}


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ClientChatWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newClientConnected(QTcpSocket * client){
    auto id = client->property("id").toInt();
    ui->listClients->addItem(QString("New client added: %1").arg(id));
    auto chatWidget = new ClientChatWidget(client);
    ui->tbChats->addTab(chatWidget, QString("Client %1").arg(id));

}

void MainWindow::clientDisconnected(QTcpSocket * client){
     auto id = client->property("id").toInt();
     ui->listClients->addItem(QString("Client disconnected: %1").arg(id));
}

void MainWindow::setupServer(){
     _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &MainWindow::newClientConnected);
     connect(_server, &ServerManager::clientDisconnected, this, &MainWindow::clientDisconnected);
}

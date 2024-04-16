#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    _client = new ClientManager();
    connect(_client, &ClientManager::connected, [this](){
        ui->centralwidget->setEnabled(true);
    });
    connect(_client, &ClientManager::disconnected, [this](){
        ui->centralwidget->setEnabled(false);
    });
    connect(_client, &ClientManager::textMessageReceived, this, &MainWindow::dataReceived);
    connect(_client, &ClientManager::isTyping, this, &MainWindow::onTyping);
    connect(ui->lnMessage, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);
    _client->connectToServer();
}

void MainWindow::dataReceived(QString message){
    // ui->listMessages->addItem(data);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->listMessages->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(200, 200, 200));
    ui->listMessages->setItemWidget(listItemWidget,chatWidget);
}

void MainWindow::on_btnSend_pressed()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage(message);
    // ui->listMessages->addItem(message);
    ui->lnMessage->setText("");

    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message, true);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->listMessages->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(148, 202, 255));
    ui->listMessages->setItemWidget(listItemWidget,chatWidget);
}


void MainWindow::on_lnClientName_editingFinished()
{
    auto name = ui->lnClientName->text().trimmed();
    _client->sendName(name);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    auto status = (ChatProtocol::Status)index;
    _client->sendStatus(status);
}



void MainWindow::onTyping()
{
    statusBar()->showMessage("Server is typing...", 750);
}


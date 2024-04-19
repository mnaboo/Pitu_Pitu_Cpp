#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ServerManager.h"
#include "ChatProtocol.h"
#include "ClientChatWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newClientConnected(QTcpSocket *client);
    void clientDisconnected(QTcpSocket *client);
    void setClientName(QString prevName, QString name);
    void setClientStatus(ChatProtocol::Status status);
    void on_tbChats_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    ServerManager *_server;

    void setupServer();
};
#endif // MAINWINDOW_H

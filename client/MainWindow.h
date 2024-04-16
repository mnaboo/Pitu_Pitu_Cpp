#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientManager.h"
#include "ChatItemWidget.h"

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
    void on_actionConnect_triggered();
    void dataReceived(QString data);

    // void on_btnSend_clicked();

    void on_lnClientName_editingFinished();

    void on_btnSend_pressed();

    void on_comboBox_currentIndexChanged(int index);

    // void on_lnMessage_textChanged(const QString &arg1);

    void onTyping();

private:
    Ui::MainWindow *ui;
    ClientManager *_client;
};
#endif // MAINWINDOW_H

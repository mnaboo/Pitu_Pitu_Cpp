#include "ChatItemWidget.h"
#include "ui_ChatItemWidget.h"

ChatItemWidget::ChatItemWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatItemWidget)
{
    ui->setupUi(this);
}

ChatItemWidget::~ChatItemWidget()
{
    delete ui;
}

void ChatItemWidget::setMessage(QString message, bool isMyMessage ){
    if(isMyMessage){
        ui->lblMessage->setAlignment(Qt::AlignRight);
    }
    ui->lblMessage->setText(message);
    ui->lblTime->setText(QDateTime::currentDateTime().toString("HH:mm"));
}

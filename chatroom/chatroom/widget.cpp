#include "widget.h"
#include "./ui_widget.h"
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>
Widget::Widget(QWidget *parent, QString name)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_name = name;

    this->port = 9999;
    this->udpSocket = new QUdpSocket(this);

    udpSocket->bind(this->port,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    //
    connect(udpSocket, &QUdpSocket::readyRead,this,&Widget::RecvMsg);

    // 链接发送按钮
    connect(ui->sendButton,&QPushButton::clicked,[=](){
        sendMsg(Msg);
    });

    // 新用户进入
    sendMsg(UserEnter);

    // 链接退出按钮
    connect(ui->quitButton,&QPushButton::clicked,[=](){
        this->close();
    });

    connect(ui->clearButton,&QPushButton::clicked,[=](){
        ui->msgTextEdit->clear();
        ui->msgTextEdit->setFocus();
    });
}

void Widget::sendMsg(Widget::MsgType type){
    QByteArray array;
    QDataStream stream(&array,QIODevice::WriteOnly);

    stream<<type<<this->getName();
    switch (type) {
    case Msg:

        if(this->ui->msgTextEdit->toPlainText() == ""){
            QMessageBox::warning(this,"警告","发送的聊天内容不能为空！");
            return;
        }
        stream<<this->getMsg();
        break;
    case UserEnter:
        break;
    case UserLeft:
        break;
    }
    // 书写报文
    udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);// QHostAddress::Broadcast：要发送的ip地址，这里发送给所有人
}

void Widget::RecvMsg(){
    qint64 size = udpSocket->pendingDatagramSize();// 获取发送过来的报文大小
    //qint64转int
    int m_size = static_cast<int>(size);
    QByteArray *array=new QByteArray(m_size,0);
    udpSocket->readDatagram(array->data(),size);//读取报文
    QDataStream stream(array,QIODevice::ReadOnly);
    int msgtype;
    stream>>msgtype; // 读取消息类型
    QString name,msg;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    switch (msgtype) {
    case Msg:
        stream>>name>>msg; // 流出姓名和聊天内容

        // 增加聊天记录
        ui->MsgBrowser->setTextColor(Qt::blue);
        ui->MsgBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->MsgBrowser->append("["+name+"]"+time);
        ui->MsgBrowser->append(msg);
        break;
    case UserEnter:
        stream>>name;
        userEnter(name);
        break;
    case UserLeft:
        stream>>name;
        userLeft(name,time);
        break;
    default:
        break;
    }
}

void Widget::userEnter(QString name){
    bool isEmpty = ui->userTable->findItems(name,Qt::MatchExactly).isEmpty();//查找方式 MatchExactly

    if(isEmpty){
        QTableWidgetItem *usr = new QTableWidgetItem(name);
        ui->userTable->insertRow(0);
        ui->userTable->setItem(0,0,usr);
        ui->MsgBrowser->setTextColor(Qt::gray);
        ui->MsgBrowser->append(name+"已上线");
        ui->onlinepeople->setText(QString("在线人数：%1人").arg(ui->userTable->rowCount()));

        sendMsg(UserEnter);
    }
}

void Widget::userLeft(QString name,QString time){
    bool isEmpty = ui->userTable->findItems(name,Qt::MatchExactly).isEmpty();

    if(!isEmpty){
        //寻找行
        int row = ui->userTable->findItems(name,Qt::MatchExactly).first()->row();
        //移除该行
        ui->userTable->removeRow(row);
        //追加信息
        ui->MsgBrowser->setTextColor(Qt::gray);
        ui->MsgBrowser->append(name+"于"+time+"下线");
        ui->onlinepeople->setText(QString("在线人数：%1人").arg(ui->userTable->rowCount()));

    }
}

QString Widget::getName(){
    return this->m_name;
}

QString Widget::getMsg(){
    QString msg = ui->msgTextEdit->toHtml();// 返回输入框的内容
    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
    return msg;
}


void Widget::closeEvent(QCloseEvent *){
    emit this->closeWidget();
    sendMsg(UserLeft);

    udpSocket->close();
    udpSocket->destroyed();
}

Widget::~Widget()
{
    delete ui;
}

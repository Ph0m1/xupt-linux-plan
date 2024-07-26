#include "widget.h"
#include "./ui_widget.h"
#include <QDataStream>
#include <QMessageBox>
#include "mysocket.h"
#include <QDateTime>

Widget::Widget(QWidget *parent, QString uname, QString uid, QString id, QString name,int sfd)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_name = name;
    m_id = id;
    u_id = uid;
    u_name = uname;

    // 链接发送按钮
    connect(ui->sendButton,&QPushButton::clicked,[=](){
        SendMsg();
        qDebug() << "Sender: "<< m_name ;
    });

    // 链接退出按钮
    connect(ui->quitButton,&QPushButton::clicked,[=](){
        this->close();
    });
    // 链接清除按钮
    connect(ui->clearButton,&QPushButton::clicked,[=](){
        ui->msgTextEdit->clear();
        ui->msgTextEdit->setFocus();
    });

    // 设置字体
    connect(ui->fontComboBox,&QFontComboBox::currentFontChanged,[=](const QFont &font){
        ui->msgTextEdit->setFontFamily(font.toString());
        ui->msgTextEdit->setFocus();
    });

    // 设置字体大小
    void (QComboBox:: * sizebox)(const QString &text) = &QComboBox::currentTextChanged;
    connect(ui->sizeBox,sizebox,[=](const QString &text){
        ui->msgTextEdit->setFontPointSize(text.toDouble());
        ui->msgTextEdit->setFocus();
    });

    // 以下参数均为bool类型
        // 加粗
    connect(ui->strongButton,&QToolButton::clicked,[=](bool checked){
        if(checked){
            ui->msgTextEdit->setFontWeight(QFont::Bold);
        }
        else{
            ui->msgTextEdit->setFontWeight(QFont::Normal);
        }
        ui->msgTextEdit->setFocus();
    });
        // 倾斜
    connect(ui->itllicButton,&QToolButton::clicked,[=](bool checked){
        ui->msgTextEdit->setFontItalic(checked);
        ui->msgTextEdit->setFocus();
    });
        // 下划线
    connect(ui->underlineButton,&QToolButton::clicked,[=](bool checked){
        ui->msgTextEdit->setFontUnderline(checked);
        ui->msgTextEdit->setFocus();
    });
}

void Widget::SendMsg(){
    QString mm = getMsg();
    std::string msg = m_id.toStdString() + u_id.toStdString() + mm.toStdString();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    std::string t = time.toStdString();
    Json stream;
    stream["Time"] = t;
    stream["Msg"] = msg;
    std::string data = stream.dump();
    sendMsg(fd, Msg, data);
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

void Widget::getData(std::string data){
    Json js = Json::parse(data.data());
    std::string msg = js["Msg"].get<std::string>();
    std::string time = js["Time"].get<std::string>();
    std::string sender = msg.substr(0,9);
    std::string uid = u_id.toStdString();
    if(uid != sender){
        return;
    }
    prints(time, msg.substr(18));
}
// 打印通知
void Widget::printinfo(std::string msg){
    ui->MsgBrowser->setTextColor(Qt::gray);
    ui->MsgBrowser->append(msg.c_str());
}
// 打印消息
void Widget::prints(std::string time, std::string msg){
    ui->MsgBrowser->setTextColor(Qt::blue);
    ui->MsgBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->MsgBrowser->append("["+u_name+"]" + static_cast<QString>(time.c_str()));
    ui->MsgBrowser->append(msg.c_str());
}
void Widget::closeEvent(QCloseEvent *){
    emit this->closeWidget();
    // sendMsg(UserLeft);
}

Widget::~Widget()
{
    delete ui;
}

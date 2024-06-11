#include "found.h"
#include "ui_found.h"
#include "setnewpasswd.h"
#include "mysocket.h"
#include <QMessageBox>
Found::Found(QWidget *parent,int sfd)
    : QWidget(parent)
    , ui(new Ui::Found)
    , fd(sfd)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("找回密码");
    // 设置发送验证码按钮
    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        //发送验证码
        std::string mail = ui->mailEdit->text().toStdString().c_str();
        sendMsg(fd,AccountFound,mail);
        MsgType a = recvMsg(fd);

    });
    // 设置校验验证码按钮
    connect(ui->confrimButton,&QPushButton::clicked,[=](){
        // 比较验证码
        std::string code = ui->codeEdit->text().toStdString().c_str();
        sendMsg(fd,Captcha,code);
        std::string a;
        MsgType status = recvMsg(fd,a);
        if(status == Refuse){
            QMessageBox::warning(this, "警告","验证码错误，请重试！");
            return;
        }
        SetNewPasswd *w = new SetNewPasswd(nullptr,sfd);
        w->show();
        this->close();
    });
}

Found::~Found()
{
    delete ui;
}

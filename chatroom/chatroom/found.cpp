#include "found.h"
#include "ui_found.h"
#include "setnewpasswd.h"
Found::Found(QWidget *parent,int sfd)
    : QWidget(parent)
    , ui(new Ui::Found)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("找回密码");
    // 设置发送验证码按钮
    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        //发送验证码

    });
    // 设置校验验证码按钮
    connect(ui->confrimButton,&QPushButton::clicked,[=](){
        // 比较验证码
        SetNewPasswd *w = new SetNewPasswd(nullptr,sfd);
        w->show();
        this->close();
    });
}

Found::~Found()
{
    delete ui;
}

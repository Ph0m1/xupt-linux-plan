#include "setnewpasswd.h"
#include "ui_setnewpasswd.h"
#include "log.h"
SetNewPasswd::SetNewPasswd(QWidget *parent,int sfd)
    : QWidget(parent)
    , ui(new Ui::SetNewPasswd)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("请确认你的密码");
    // 确认修改密码
    connect(ui->yesBtn,&QPushButton::clicked,[=](){
        QString qstr = ui->newpasswdEdit->text();
    });

    connect(ui->quitBtn,&QPushButton::clicked,[=](){
        this->close();
        class log *w = new class log(this,sfd);
        w->show();
    });
}

SetNewPasswd::~SetNewPasswd()
{
    delete ui;
}

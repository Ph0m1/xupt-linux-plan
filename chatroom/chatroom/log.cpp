#include "log.h"
#include "ui_log.h"
#include "reg.h"
#include "menu.h"
#include "found.h"
#include <QMessageBox>
log::log(QWidget *parent,QString id,int sfd)
    : QWidget(parent)
    , ui(new Ui::log)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("Ph0m's chatroom");
    // 设置退出按钮
    if(!id.isEmpty()){
        ui->uid_input->setText(id);
        ui->passwd_input->setFocus();
    }
    connect(ui->quit,&QPushButton::clicked,[=](){
        this->close();
    });
    // 设置登陆按钮
    connect(ui->yes,&QPushButton::clicked,[=](){
        if(ui->uid_input->text().isEmpty()){
            QMessageBox::warning(this,"警告","请填写帐号或邮箱");
            ui->uid_input->focusProxy();
            return ;
        }
        if(ui->passwd_input->text().isEmpty()){
            QMessageBox::warning(this,"警告","请填写密码");
            ui->passwd_input->focusProxy();
            return;
        }
        nlohmann::json js;
        int id = atoi(ui->uid_input->text().toStdString().c_str());
        std::string passwd = ui->passwd_input->text().toStdString();

        js["id"] = id;
        js["passwd"] = passwd;
        std::string data = js.dump();
        std::cout<<"5656546767636423746327846"<<std::endl;
        sendMsg(sfd, UserLogin,data);
        std::cout<<"99879798789sd78as78"<<std::endl;
        std::string remsg;
        MsgType a = recvMsg(sfd,remsg);
        std::cout<<"sdha"<<std::endl;
        if(a == Success){
            this->close();
            menu *wt = new menu(nullptr,sfd,remsg);
            wt->show();
        }
        else if (a == Failure){
            ui->passwd_input->clear();
            QMessageBox::warning(this,"警告","帐号或密码错误，请重试");
        }
    });
    // 设置注册按钮
    connect(ui->resButton,&QPushButton::clicked,[=](){
        this->close();
        class reg *widget = new class reg(nullptr,sfd);
        widget->show();
    });

    // 设置忘记密码按钮
    connect(ui->foundButton,&QPushButton::clicked,[=](){
        // this->close();
        Found *w = new Found(nullptr,sfd);
        w->show();
    });
}

log::log(QWidget *parent,int sfd)
    : QWidget(parent)
    , ui(new Ui::log)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("Ph0m's chatroom");
    // 设置退出按钮
    connect(ui->quit,&QPushButton::clicked,[=](){
        this->close();
    });
    // 设置登陆按钮
    connect(ui->yes,&QPushButton::clicked,[=](){
        try{if(ui->uid_input->text().isEmpty()){

            QMessageBox::warning(this,"警告","请填写帐号或邮箱");
            ui->uid_input->focusProxy();
        }
        if(ui->passwd_input->text().isEmpty()){

            QMessageBox::warning(this,"警告","请填写密码");
            ui->passwd_input->focusProxy();
        }
        nlohmann::json js;
        int id = atoi(ui->uid_input->text().toStdString().c_str());
        std::string passwd = ui->passwd_input->text().toStdString();

        js["id"] = id;
        js["passwd"] = passwd;
        std::string data = js.dump();
        sendMsg(sfd, UserLogin,data);
        std::string remsg;
        MsgType a = recvMsg(sfd,remsg);
        std::cout<<"sdha"<<std::endl;
        if(a == Success){
            this->close();
            menu *wt = new menu(nullptr,sfd);
            wt->show();
        }
        else if (a == Failure){
            ui->passwd_input->clear();
            QMessageBox::warning(this,"警告","帐号或密码错误，请重试");
        }
        }catch (const std::exception& e) {
            QMessageBox::critical(this, "错误", QString::fromStdString(e.what()));
        } catch (...) {
            QMessageBox::critical(this, "错误", "发生未知错误");
        }
    });
    // 设置注册按钮
    connect(ui->resButton,&QPushButton::clicked,[=](){
        this->close();
        reg *widget = new reg(nullptr,sfd);
        widget->show();
    });
}

log::~log()
{
    delete ui;
}

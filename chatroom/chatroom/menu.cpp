#include "menu.h"
#include "ui_menu.h"
#include <QToolButton>
#include <QPixmap>
#include <QMessageBox>
#include "widget.h"
using json = nlohmann::json;
menu::menu(QWidget *parent,int sfd,const std::string &data)
    : QWidget(parent)
    , fd(sfd)
    , ui(new Ui::menu)
{
    //解析data数据包

        json datajs = json::parse(data.data());
        std::string info = datajs["Info"].get<std::string>();
        json infojs = json::parse(info);

        std::unordered_map<std::string,std::string> fl = datajs["FriendList"].get<std::unordered_map<std::string,std::string>>();
        std::unordered_map<std::string,std::string> gl = datajs["GroupList"].get<std::unordered_map<std::string,std::string>>();
        std::unordered_map<std::string,std::string> ml = datajs["MsgList"].get<std::unordered_map<std::string,std::string>>();

        std::string user = infojs["username"];
        std::string id = infojs[""];


    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle(user.c_str());

}

menu::~menu()
{
    delete ui;
}
void menu::setFbtn( std::unordered_map<std::string,std::string> list){
    QVector<QToolButton*> vector;
    for(auto &t : list){
        QToolButton *btn = new QToolButton(this);
        // 加载图标
        btn -> setIcon(QPixmap(":/Header/Header.jpeg"));
        // 设置图片大小
        QPixmap h(":/Header/Header.jpeg") ;
        h = h.scaled(48,48,Qt::KeepAspectRatio, Qt::SmoothTransformation);

        btn->setIconSize(h.size());
        // 设置按钮样式 透明
        btn->setAutoRaise(true);
        // 设置网名
        btn->setText(QString(static_cast<QString>(t.second.c_str()) + "<" + static_cast<QString>(t.first.c_str())) + ">");

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        ui->friendslistLayout->addWidget(btn);
        vector.push_back(btn);
        FriendIsShow.push_back(false);
    }

    for(int i = 0; i < vector.count(); i++){
        connect(vector[i], &QToolButton::clicked,[=](){
            if(FriendIsShow[i]){
                QMessageBox::warning(this, "警告","该聊天框已被打开！");
                return;
            }
            FriendIsShow[i] = true;
            Widget *widget = new Widget(nullptr,vector[i]->text(),fd);
            widget->setWindowIcon(vector[i]->icon());
            widget->setWindowTitle(vector[i]->text());
            widget->show();
        });
    }
}
void menu::setGbtn(std::unordered_map<std::string,std::string> list){

}
void menu::setMbtn(std::unordered_map<std::string,std::string> list){

}

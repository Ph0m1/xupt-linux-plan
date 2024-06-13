#include "menu.h"
#include "ui_menu.h"
#include <QToolButton>
#include <QPixmap>
#include <QMessageBox>
#include "widget.h"
#include "settings.h"
using json = nlohmann::json;
menu::menu(QWidget *parent,int sfd,const std::string &data)
    : QWidget(parent)
    , fd(sfd)
    , ui(new Ui::menu)
{
    //解析data数据包
        std::cout<<data<<std::endl;
        json datajs = json::parse(data.data());

        json infojs = datajs["Info"].get<json>();

        std::unordered_map<std::string,std::string> fl = datajs["FriendList"].get<std::unordered_map<std::string,std::string>>();
        std::unordered_map<std::string,std::string> gl = datajs["GroupList"].get<std::unordered_map<std::string,std::string>>();
        std::unordered_map<std::string,std::string> ml = datajs["MsgList"].get<std::unordered_map<std::string,std::string>>();

        std::string user;
        user = infojs["username"].get<std::string>();
        std::string id;
        this->id = id;
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("Rooms");
    ui->personalBtn->setIcon(QPixmap(":/Header/Header.jpeg"));
    // 设置图片大小
    QPixmap h(":/Header/Header.jpeg") ;
    h = h.scaled(56,56,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->personalBtn->setIconSize(h.size());
    ui->personalBtn->setAutoRaise(true);
    ui->personalBtn->setText(user.c_str());
    ui->personalBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    setFbtn(fl);
    setGbtn(gl);
    connect(ui->SearchFriendBtn,&QPushButton::clicked,[=](){

    });

    connect(ui->personalBtn,&QToolButton::clicked,[=](){
        class Settings w;
        w.show();
    });

    connect(ui->SearchFriendBtn,&QPushButton::clicked,[=](){
        std::string aimmer = ui->SearchFriendEdit->text().toStdString();
        sendMsg(fd, FriendAdd, aimmer);
        QMessageBox::information(this,"提示","已发送好友请求");
    });

    connect(ui->JoinGroupBtn,&QPushButton::clicked,[=](){
        std::string aimmer = ui->SearchGroupBtn->text().toStdString();
        sendMsg(fd,GroupJoin,aimmer);
        QMessageBox::information(this,"提示","已发送加入请求");
    });

}

menu::~menu()
{
    sendMsg(fd,OutLine,id);
    delete ui;
}
void menu::setFbtn( std::unordered_map<std::string,std::string> list){
    QVector<QToolButton*> vector;
    QVBoxLayout *layout = new QVBoxLayout();
    for(auto &t : list){
        if (t.first == " "){
            break;
        }
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

        layout->addWidget(btn);
        vector.push_back(btn);
        FriendIsShow.push_back(false);
    }
    ui->layoutfriend->addLayout(layout);

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

            // 关闭时将Isshow改为false
            connect(widget, &Widget::closeWidget,this,[=](){
                FriendIsShow[i] = false;
            });
        });
    }
}
void menu::setGbtn(std::unordered_map<std::string,std::string> list){
    QVector<QToolButton*> vector;
        QVBoxLayout *layout = new QVBoxLayout();
    for(auto &t : list){
        if (t.first == " "){
            break;
        }
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
        btn->setText(QString(static_cast<QString>(t.second.c_str()) ));

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        layout->addWidget(btn);
        vector.push_back(btn);
        GroupIsShow.push_back(false);
    }
    ui->grouplayout->addLayout(layout);


    for(int i = 0; i < vector.count(); i++){
        connect(vector[i], &QToolButton::clicked,[=](){
            if(GroupIsShow[i]){
                QMessageBox::warning(this, "警告","该聊天框已被打开！");
                return;
            }
            GroupIsShow[i] = true;
            Widget *widget = new Widget(nullptr,vector[i]->text(),fd);
            widget->setWindowIcon(vector[i]->icon());
            widget->setWindowTitle(vector[i]->text());
            widget->show();
            // 关闭时将Isshow改为false
            connect(widget, &Widget::closeWidget,this,[=](){
                GroupIsShow[i] = false;
            });
        });
    }
}
// void menu::setMbtn(std::unordered_map<std::string,std::string> list){

// }

#include "menu.h"
#include "ui_menu.h"
#include <QToolButton>
#include <QPixmap>
#include <QMessageBox>
#include "widget.h"
menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("Ph0m's chatroom");
    QVector<QToolButton*> vector;
    for(int i = 0;i < 89;i++){
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
        btn->setText(QString("啊木木"+static_cast<QString>(i)));

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        ui->friendslistLayout->addWidget(btn);
        vector.push_back(btn);
        IsShow.push_back(false);
    }

    for(int i =0 ;i<vector.count();i++){
        connect(vector[i], &QToolButton::clicked,[=](){
            if(IsShow[i]){
                QMessageBox::warning(this, "警告","该聊天框已被打开！");
                // vector[i]->setFocus();
                return;
            }
            IsShow[i] = true;
            Widget *widget = new Widget(nullptr,vector[i]->text());
            widget->setWindowIcon(vector[i]->icon());
            widget->setWindowTitle(vector[i]->text());
            widget->show();

            // 关闭时将isShow改为false
            connect(widget,&Widget::closeWidget,this,[=](){
                IsShow[i] = false;
            });
        });
    }
}

menu::~menu()
{
    delete ui;
}

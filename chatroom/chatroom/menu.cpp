#include "menu.h"
#include "ui_menu.h"
#include <QToolButton>
#include <QPixmap>

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("Ph0m's chatroom");

    for(int i = 0;i < 89;i++){
        QToolButton *btn = new QToolButton(this);
        // 加载图标
        btn -> setIcon(QPixmap(":/Header/Header.jpeg"));
        // 设置图片大小
        QPixmap h(":/Header/Header.jpeg") ;
        h = h.scaled(32,32,Qt::KeepAspectRatio, Qt::SmoothTransformation);

        btn->setIconSize(h.size());
        // 设置网名
        btn->setText(QString("啊木木"));

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        ui->friendslistLayout->addWidget(btn);
    }
}

menu::~menu()
{
    delete ui;
}

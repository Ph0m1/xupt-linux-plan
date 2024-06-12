#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));


    connect(ui->pushButton_2,&QPushButton::clicked,[=](){

    });

}

Settings::~Settings()
{
    delete ui;
}

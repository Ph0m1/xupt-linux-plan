#include "log.h"
#include "ui_log.h"

log::log(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::log)
{
    ui->setupUi(this);
    // 设置图标
    this->setWindowIcon(QIcon(":/Header/Header.jpeg"));
    // 设置名称
    this->setWindowTitle("Ph0m's chatroom");
}

log::~log()
{
    delete ui;
}

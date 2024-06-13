#include "menu2.h"
#include "ui_menu2.h"

Menu2::Menu2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu2)
{
    ui->setupUi(this);
}

Menu2::~Menu2()
{
    delete ui;
}

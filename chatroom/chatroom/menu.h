#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "mysocket.h"
namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent,int sfd);
    ~menu();

private:
    Ui::menu *ui;
    QVector<bool> IsShow;
};

#endif // MENU_H

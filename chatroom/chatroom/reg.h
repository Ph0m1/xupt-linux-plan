#ifndef REG_H
#define REG_H

#include "mysocket.h"
#include <QWidget>

namespace Ui {
class reg;
}

class reg : public QWidget
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent,int sfd);
    ~reg();

private:
    Ui::reg *ui;
};

#endif // REG_H

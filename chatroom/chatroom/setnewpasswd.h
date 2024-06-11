#ifndef SETNEWPASSWD_H
#define SETNEWPASSWD_H

#include "mysocket.h"
#include <QWidget>

namespace Ui {
class SetNewPasswd;
}

class SetNewPasswd : public QWidget
{
    Q_OBJECT

public:
    explicit SetNewPasswd(QWidget *parent,int sfd);
    ~SetNewPasswd();

private:
    Ui::SetNewPasswd *ui;
    int fd;
};

#endif // SETNEWPASSWD_H

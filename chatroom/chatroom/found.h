#ifndef FOUND_H
#define FOUND_H

#include <QWidget>
#include "mysocket.h"
namespace Ui {
class Found;
}

class Found : public QWidget
{
    Q_OBJECT

public:
    explicit Found(QWidget *parent, int sfd);
    explicit Found(QWidget *parent, int sfd, int tmp);
    ~Found();

private:
    Ui::Found *ui;
    int fd;
};

#endif // FOUND_H

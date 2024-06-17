#ifndef MENU2_H
#define MENU2_H

#include <QWidget>
#include <QToolButton>
#include <QPixmap>
#include <QMessageBox>

namespace Ui {
class Menu2;
}

class Menu2 : public QWidget
{
    Q_OBJECT

public:
    explicit Menu2(QWidget *parent, int sfd,const std::string &data);
    ~Menu2();
private:
    void setFbtn(std::unordered_map<std::string,std::string> list);
    void setGbtn(std::unordered_map<std::string,std::string> list);
    // void setMbtn(std::unordered_map<std::string,std::string> list);

private:
    Ui::Menu2 *ui;
    int fd;
    std::string id;

    QVector<bool> FriendIsShow;
    QVector<bool> GroupIsShow;
    QVector<bool> IsRead;
};

#endif // MENU2_H

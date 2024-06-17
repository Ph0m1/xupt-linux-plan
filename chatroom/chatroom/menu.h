#ifndef MENU_H
#define MENU_H

#include <QWidget>
namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent,int sfd,const std::string &list);
    ~menu();
private:
    void setFbtn(std::unordered_map<std::string,std::string> list);
    void setGbtn(std::unordered_map<std::string,std::string> list);
    // void setMbtn(std::unordered_map<std::string,std::string> list);
private:
    Ui::menu *ui;

    QVector<bool> FriendIsShow;
    QVector<bool> GroupIsShow;
    QVector<bool> IsRead;
    int fd;
    std::string id;
};

#endif // MENU_H

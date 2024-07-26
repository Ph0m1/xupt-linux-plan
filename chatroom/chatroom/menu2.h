#ifndef MENU2_H
#define MENU2_H

#include <QWidget>
#include <QToolButton>
#include <QPixmap>
#include <QMap>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QStackedWidget>

#include "widget.h"
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
    void setMbtn(std::unordered_map<std::string,std::string> list);
    void printmsg(std::string user, std::string msg, int flag, Widget* w);
    // 复制widget及其布局
    QWidget* copyWidget(QWidget* widget);

    void readFromServer(int fd);
    void printmsg(std::string msg);

signals:
    void sendData(std::string msg);
private:
    Ui::Menu2 *ui;
    int fd;
    std::string m_id;
    std::string m_name;

    QVector<bool> FriendIsShow;
    QVector<bool> GroupIsShow;
    QVector<bool> MsgIsShow;
    QVector<bool> MsgIsOn;
    QVector<Widget*> ww;
    bool btnIsChecked[2];

    QVector<QToolButton*> vector;// 好友按钮
    std::unordered_map<std::string, QToolButton*> lists;
    QVector<QToolButton*> msglist;
    QStackedWidget *qStack = new QStackedWidget(this); // 聊天窗口
    // QStackedWidget *listStack; // 消息/好友列表
};

#endif // MENU2_H

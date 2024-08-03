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
#include <QDebug>

#include "settings.h"
#include "threadpool.h"
#include "badgetoolbutton.h"
#include "informations.h"
#include "creategroupdialog.h"

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
    void resetFbtn(const std::string &str);
    void setFbtn(std::unordered_map<std::string,std::string> list);
    void setMbtn(std::unordered_map<std::string,std::string> list);
    void printmsg(std::string user, std::string msg, int flag, Widget* w);
    // 复制widget及其布局
    QWidget* copyWidget(QWidget* widget);
    void pauseMsgThread();//暂停
    void resumeMsgThread();//重新唤醒

    void createGroup(const std::vector<std::string> &ll);

    void readFromServer(int fd);
    ThreadPool *threadPool;

private:
    Ui::Menu2 *ui;
    int fd;
    std::string m_id;
    std::string m_name;
    std::vector<std::string> friendaddlist;

    Settings *setting = new Settings;
    informations *w;
    BadgeToolButton *friendaddbtn;
    QVBoxLayout *layout;
    QVector<bool> FriendIsShow;
    QVector<bool> GroupIsShow;
    QVector<bool> MsgIsShow;
    QVector<bool> MsgIsOn;
    QVector<Widget*> ww;
    bool btnIsChecked[2];

    QVector<BadgeToolButton*> vector;// 好友按钮
    std::unordered_map<std::string, BadgeToolButton*> lists;
    std::unordered_map<std::string, std::string> friendlist;
    QStackedWidget *qStack = new QStackedWidget(this); // 聊天窗口
    // QStackedLayout *listStack = new QStackedLayout(this); // 消息/好友列表
signals:
    void sendinfos(std::string ll);
    void sendlist(std::vector<std::string> ll);
    void sendData(std::string msg);
    void friendsg(std::string msg);
    void refreshFriendList(std::string list);
    void friendaddmsg(std::string str);
    void addRowList(std::string str);
public slots:
    void updatefriendaddbtn(std::string id);
    void updateList(std::string id);
    void friendAdd(std::string msg);
    void updateFriendList(std::string list);
    void deleteAccont();
    void exit();
private slots:
    void showCreateGroupDialog();
};

#endif // MENU2_H

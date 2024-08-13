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
#include "createfrienddialog.h"

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
    void setFbtn(std::unordered_map<std::string,std::string> list, int flag,
                    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> gmm);
    void setMbtn(std::unordered_map<std::string,std::string> list);
    void printmsg(std::string user, std::string msg, int flag, Widget* w);
    // 复制widget及其布局
    QWidget* copyWidget(QWidget* widget);


    void createGroup(const std::vector<std::string> &ll, const std::string & name);
    void deletefriends(const std::vector<std::string> &ll);
    void readFromServer(int fd);

    void sendfileinfo(std::string fileinfo);

    ThreadPool *threadPool;

private:
    Ui::Menu2 *ui;
    int fd;
    std::string m_id;
    std::string m_name;
    std::vector<std::string> friendaddlist;// 好友申请列表
    std::vector<std::string> groupinfolist;// 群通知按钮

    Settings *setting = new Settings;
    informations *w; // 好友申请处理界面
    informations *w2; // 群通知处理界面
    BadgeToolButton *friendaddbtn;
    BadgeToolButton * groupinfobtn;
    QVBoxLayout *layout;
    QVector<bool> FriendIsShow;
    QVector<bool> GroupIsShow;
    QVector<bool> MsgIsShow;
    QVector<bool> MsgIsOn;
    QVector<Widget*> ww;
    bool btnIsChecked[2];

    std::mutex pauseMutex;
    std::condition_variable pauseCondition;
    bool pauseThread = false;

    QVector<BadgeToolButton*> vector;// 按钮
    std::unordered_map<std::string, BadgeToolButton*> lists; // 按钮
    std::unordered_map<std::string, std::string> friendlist;
    std::unordered_map<std::string, std::string> grouplist;
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
    void receivedfile(std::string fileinfo);
    void fileinfos(std::string fileinfo);
public slots:
    void updatefriendaddbtn(std::string id);
    void updateList(std::string id);
    void friendAdd(std::string msg);
    void updateFriendList(std::string list);
    void deleteAccont();
    void exit();

    void pause();
    void resume();

    void fileinfo(std::string fileinfo);
    void recvfile(std::string fileinfo);
private slots:
    void showCreateGroupDialog();
    void showDeleteFriendDialog();
};

#endif // MENU2_H

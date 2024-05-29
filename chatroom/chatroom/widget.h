#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include "mysocket.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent,QString name,int sfd);
    // 枚举 普通信息 用户上线 用户离线
    enum MsgType{Msg,UserEnter,UserLeft};
    void sendMsg(MsgType type); // 广播UDP信息
    QString getName();// 获取名字
    QString getMsg();// 获取信息
    void userEnter(QString username);// 处理用户上线
    void userLeft(QString username,QString time);// 处理用户下线
    void RecvMsg();// 接受udp消息

    ~Widget();
signals:
    //关闭窗口信号
    void closeWidget();
private:
    Ui::Widget *ui;
    QString m_name;
    quint16 port;
    QUdpSocket *udpSocket;// Udp套接字
public:
    // 重写关闭事件
    void closeEvent(QCloseEvent*);
};
#endif // WIDGET_H

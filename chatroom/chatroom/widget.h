#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mysocket.h"
#include <QDebug>
using Json = nlohmann::json;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent,QString uname, QString uid, QString id, QString name,int sfd);
    QString getName();// 获取名字
    QString getMsg();// 获取信息
    void SendMsg();
    void prints(std::string time, std::string msg);
    void printinfo(std::string msg);
    ~Widget();
signals:
    //关闭窗口信号
    void closeWidget();

    public slots:
    void getData(std::string data);

private:
    Ui::Widget *ui;
    QString m_name;
    QString m_id;
    QString u_id;
    QString u_name;
    int fd;
public:
    // 重写关闭事件
    void closeEvent(QCloseEvent*);
};
#endif // WIDGET_H

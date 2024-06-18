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
    // void setMbtn(std::unordered_map<std::string,std::string> list);
    // 复制widget及其布局
    QWidget* copyWidget(QWidget* widget);

private:
    Ui::Menu2 *ui;
    int fd;
    std::string id;

    QVector<bool> FriendIsShow;
    QVector<bool> GroupIsShow;
    QVector<bool> IsRead;

    QVector<QToolButton*> vector;
    QMap<QToolButton*,QVBoxLayout*> lists;

    QStackedWidget *qStack;
};

#endif // MENU2_H

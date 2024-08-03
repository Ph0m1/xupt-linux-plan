#ifndef CREATEGROUPDIALOG_H
#define CREATEGROUPDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>


class CreateGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGroupDialog(QWidget *parent , const std::unordered_map<std::string, std::string> &friends);
    std::vector<std::string> getSelectedFriends() const;

private:
    QListWidget *friendListWidget;
    QPushButton *creatBtn;
    std::unordered_map<std::string, std::string> friendList;

private slots:
    void onCreateBtnClicked();
};

#endif // CREATEGROUPDIALOG_H

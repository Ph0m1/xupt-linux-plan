#ifndef CUSTOMTABLEWIDGETITEM_H
#define CUSTOMTABLEWIDGETITEM_H

#include <QApplication>
#include <QTableWidgetItem>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QActionEvent>
#include <QTableWidget>
#include <QObject>

class CustomTableWidgetItem : public QTableWidgetItem
{
    Q_OBJECT
public:
    CustomTableWidgetItem(const QString &text, std::string id);

    void showContextMenu(QTableWidget *tableWidget, const QPoint &pos);
private:
    std::string id;

signals:
    void addfriend(std::string id);
    void deletemember(std::string id);
    void setmanager(std::string id);
    void cancelmanager(std::string id);
};

#endif // CUSTOMTABLEWIDGETITEM_H

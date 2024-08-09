#include "customtablewidgetitem.h"

CustomTableWidgetItem::CustomTableWidgetItem(const QString &text, std::string id)
    :QTableWidgetItem(text)
    ,id(id)
{

}

void CustomTableWidgetItem::showContextMenu(QTableWidget *tableWidget, const QPoint &pos){
    QMenu contextMenu(tableWidget);
    QAction *action1 = contextMenu.addAction("添加好友");
    QAction *action2 = contextMenu.addAction("踢出群聊");
    QAction *action3 = contextMenu.addAction("设为管理员");
    QAction *action4 = contextMenu.addAction("取消管理员");

    connect(action1, &QAction::triggered, this, [=](){
        emit addfriend(id);
    }) ;

}

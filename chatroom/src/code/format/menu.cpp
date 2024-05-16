#include "menu.hpp"
#include <QDialog>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QDialog *dialog = new QDialog;
    Ui_chatroom *ui = new Ui_chatroom;
    ui->setupUi(dialog);
    dialog->show();
    return app.exec();

}
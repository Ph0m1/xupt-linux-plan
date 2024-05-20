#include "menu.hpp"
#include <QDialog>
#include <string>
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QDialog *dialog = new QDialog;
    Ui_welcome *ui = new Ui_welcome;
    ui->setupUi(dialog);
    dialog->show();
    return app.exec();
}

class usr_input{
    //用户输入
    Ui::welcome *ui;
    public:
    usr_input(Ui::welcome *ui){
        this->ui = ui;
    }
    std::string get_reg_input(){
        Qstring q_reg1_str = ui->name_reg->text();
        //获取用户输入
        Qstring q_reg2_str = ui->name_reg->text();
        Qstring q_reg3_str = ui->passwd_reg->text();
        Qstring q_reg4_str = ui->ans->text();

        
        ui->id_log->text();
        ui->passwd_log->text();
        //TODO: 处理用户输入
    }
};
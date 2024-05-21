#include "menu.hpp"
#include "../../../include/json.hpp"
#include <QDialog>
#include <string>
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QDialog *dialog = new QDialog;
  Ui_welcome *ui = new Ui_welcome;
  ui->setupUi(dialog);
  dialog->show();
  return app.exec();
}

class welcome {
  // 用户输入
  Ui::welcome *ui;

public:
  welcome(Ui::welcome *ui) { this->ui = ui; }
  std::string get_input() {
    Qstring q_reg1_str = ui->name_reg->text();
    // 获取用户输入
    Qstring q_reg2_str = ui->name_reg->text();
    Qstring q_reg3_str = ui->passwd_reg->text();
    Qstring q_reg4_str = ui->ans->text();

    Qstring q_reg5_str = ui->id_log->text();
    Qstring q_reg6_str = ui->passwd_log->text();
    // TODO: 处理用户输入
    RapidJson log_js, reg_js;

    log_js["id"] = q_reg5_str.toStdString();
    log_js["passwd"] = q_reg6_str.toStdString();
    reg_js["name"] = q_reg1_str.toStdString();
    reg_js["passwd"] = q_reg2_str.toStdString();
    reg_js["ans"] = q_reg4_str.toStdString();

    std::string log_str = log_js.toString();
    std::string reg_str = reg_js.toString();
    if (ui->Reg->isChecked()) {
      return reg_str;
    } else if (ui->Login->isChecked()) {
      return log_str;
    } else if (ui->quit1->isChecked() || ui->quit2->isChecked()) {
        exit(0);
    }
  }
};
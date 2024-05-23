#include "menu.hpp"
#include <QDialog>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

class welcome {
  // 用户输入
  Ui::welcome *ui;
  std::unique_ptr<QDialog> dialog;

public:
  welcome(Ui::welcome *ui) { this->ui = ui; }
  welcome() {
    // 初始化界面
    ui = new Ui::welcome;
    dialog = std::make_unique<QDialog>();
    ui->setupUi(dialog.get());
    dialog->show();
  }
  std::string get_input() {
    QString q_reg1_str = ui->name_reg->text();
    // 获取用户输入
    QString q_reg2_str = ui->name_reg->text();
    QString q_reg3_str = ui->passwd_reg->text();
    QString q_reg4_str = ui->ans->text();

    QString q_reg5_str = ui->id_log->text();
    QString q_reg6_str = ui->passwd_log->text();
    // TODO: 处理用户输入
    nlohmann::json js;
    while (1) {
      if (ui->login->isChecked()) {
        std::cout << "dsdasd" << std::endl;
        js["id"] = q_reg5_str.toStdString();
        js["passwd"] = q_reg6_str.toStdString();
        break;
      } else if (ui->Reg->isChecked()) {
        js["name"] = q_reg1_str.toStdString();
        js["passwd"] = q_reg2_str.toStdString();
        js["ans"] = q_reg4_str.toStdString();
        break;
      } else if (ui->quit1->isChecked() || ui->quit2->isChecked()) {
        return "quit";
      }
    }

    return js.dump();
  }
  ~welcome() { delete ui; }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  std::unique_ptr<welcome> w = std::make_unique<welcome>();
  app.exec();
  std::string input = w->get_input();
  std::cout << input << std::endl;
  // return app.exec();
  return 0;
}
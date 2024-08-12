#include "filemenu.h"
#include "ui_filemenu.h"

FileMenu::FileMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileMenu)
{
    ui->setupUi(this);
    connect(ui->choseFile, &QPushButton::clicked, [=](){
        std::string path = getFile();
        emit filePath(path);
    });
    connect(ui->cancelbtn, &QPushButton::clicked, [=](){
        this->close();
    });
}

FileMenu::~FileMenu()
{
    delete ui;
}

std::string FileMenu::getFile(){
    QString filepath = QFileDialog::getOpenFileName(this, "选择文件", "", "所有文件(*)");
    std::string path = " ";
    if(!filepath.isEmpty()){
        QMessageBox::information(this, "文件路径", "您选择的文件路径是：\n" + filepath);
        path = filepath.toStdString();
    }
    return path;
}

#ifndef FILEMENU_H
#define FILEMENU_H

#include <QPushButton>
#include <QMessageBox>
#include <QWidget>
#include <QFileDialog>

namespace Ui {
class FileMenu;
}

class FileMenu : public QWidget
{
    Q_OBJECT

public:
    explicit FileMenu(QWidget *parent = nullptr);
    ~FileMenu();

    std::string getFile();

signals:
    void filePath(std::string path);
private:
    Ui::FileMenu *ui;
};

#endif // FILEMENU_H

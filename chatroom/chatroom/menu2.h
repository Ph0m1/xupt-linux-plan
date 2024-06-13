#ifndef MENU2_H
#define MENU2_H

#include <QWidget>

namespace Ui {
class Menu2;
}

class Menu2 : public QWidget
{
    Q_OBJECT

public:
    explicit Menu2(QWidget *parent = nullptr);
    ~Menu2();

private:
    Ui::Menu2 *ui;
};

#endif // MENU2_H

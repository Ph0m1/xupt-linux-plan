#include "menu2.h"
#include "ui_menu2.h"
#include "mysocket.h"
#include <QPainter>
#include <QPainterPath>
using json = nlohmann::json;

Menu2::Menu2(QWidget *parent, int sfd, const std::string& data)
    : QWidget(parent)
    , fd(sfd)
    , ui(new Ui::Menu2)
{

    //解析data数据包
    std::cout<<data<<std::endl;
    json datajs = json::parse(data.data());

    json infojs = datajs["Info"].get<json>();

    std::unordered_map<std::string,std::string> fl = datajs["FriendList"].get<std::unordered_map<std::string,std::string>>();
    std::unordered_map<std::string,std::string> gl = datajs["GroupList"].get<std::unordered_map<std::string,std::string>>();
    std::unordered_map<std::string,std::string> ml = datajs["MsgList"].get<std::unordered_map<std::string,std::string>>();

    std::string user;
    user = infojs["username"].get<std::string>();
    std::string id;
    this->id = id;
    ui->setupUi(this);

    // 设置图标
    this->setWindowIcon(QIcon("/Header/Header.jpeg"));

    // 设置名称
    this->setWindowTitle("Rooms");

    // 加载图像
    QPixmap pixmap(":/Header/Header.jpeg");

    // 裁剪成圆形
    QPixmap circularPixmap(pixmap.size());
    circularPixmap.fill(Qt::transparent);

    QPainter painter(&circularPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath path1;
    path1.addEllipse(0, 0, pixmap.width(), pixmap.height());
    painter.setClipPath(path1);
    painter.drawPixmap(0, 0, pixmap);

    // 设置按钮图标
    ui->infoBtn->setIcon(QIcon(circularPixmap));

    // 设置图标大小
    circularPixmap = circularPixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->infoBtn->setIconSize(circularPixmap.size());

    // 设置按钮样式
    ui->infoBtn->setAutoRaise(true);
    ui->infoBtn->setStyleSheet("background-color: none; border: none; border-radius: 25px;");

    // 设置聊天界面按钮
    QPixmap cpixmap = circularPixmap;
    cpixmap = cpixmap.scaled(32,32,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->msgBtn->setAutoRaise(true);
    ui->msgBtn->setIconSize(cpixmap.size());
    ui->friendBtn->setAutoRaise(true);
    ui->friendBtn->setIconSize(cpixmap.size());
    ui->settingBtn->setAutoRaise(true);
    ui->settingBtn->setIconSize(cpixmap.size());

    connect(ui->friendBtn,&QToolButton::clicked,[=](){
        setFbtn(fl);
    });


}

void Menu2::setFbtn(std::unordered_map<std::string,std::string> list){
    QVector<QToolButton*> vector;
    QVBoxLayout *layout = new QVBoxLayout();

    for(auto &t : list){
        if (t.first == " "){
            break;
        }
        QToolButton *btn = new QToolButton(this);
        // 加载图标
        btn -> setIcon(QPixmap(":/Header/Header.jpeg"));
        // 设置图片大小
        QPixmap h(":/Header/Header.jpeg") ;
        h = h.scaled(48,48,Qt::KeepAspectRatio, Qt::SmoothTransformation);

        btn->setIconSize(h.size());
        // 设置按钮样式 透明
        btn->setAutoRaise(true);
        // 设置网名
        btn->setText(QString(static_cast<QString>(t.second.c_str()) + "<" + static_cast<QString>(t.first.c_str())) + ">");

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setAutoRepeat(true);
        layout->addWidget(btn);
        vector.push_back(btn);
        FriendIsShow.push_back(false);

    }
    ui->listWidget->setLayout(layout);

    for(int i = 0; i < vector.count(); i++){
        connect(vector[i], &QToolButton::clicked,[=](){

            FriendIsShow[i] = true;
            // 修改信息 示例
            QWidget* widget = ui->msgWidget;
            ui->label->setText(vector[i]->text());
        });
    }

}

Menu2::~Menu2()
{
    delete ui;
}

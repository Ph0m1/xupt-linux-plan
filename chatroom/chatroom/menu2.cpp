#include "menu2.h"
#include "ui_menu2.h"
#include "mysocket.h"
#include "widget.h"
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
    //fl id:name
    //ml time(15位):<发送方id(9位)><接受方id(9位)><内容>
    std::unordered_map<std::string,std::string> fl = datajs["FriendList"].get<std::unordered_map<std::string,std::string>>();
    std::unordered_map<std::string,std::string> gl = datajs["GroupList"].get<std::unordered_map<std::string,std::string>>();
    std::unordered_map<std::string,std::string> ml = datajs["MsgList"].get<std::unordered_map<std::string,std::string>>();

    std::string user;
    user = infojs["username"].get<std::string>();
    std::cout << user;
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
    Menu2::btnIsChecked[0] = false;
    Menu2::btnIsChecked[1] = true;

    Menu2::setFbtn(fl);
    Menu2::setFbtn(ml);
    connect(ui->friendBtn,&QToolButton::clicked,[=](){
        if(Menu2::btnIsChecked[0] == true || Menu2::btnIsChecked[1] == false){
            return;
        }
        Menu2::btnIsChecked[1] = false;
        Menu2::btnIsChecked[0] = true;
        ui->msgBtn->setChecked(false);
        // ui->friendBtn->setChecked(false);
        ui->friendBtn->setChecked(true);

    });
    connect(ui->msgBtn,&QToolButton::clicked,[=](){
        if(Menu2::btnIsChecked[1] == true || Menu2::btnIsChecked[0] == false){
            return;
        }
        Menu2::btnIsChecked[1] = true;
        Menu2::btnIsChecked[0] = false;
        ui->friendBtn->setChecked(false);
    });
}

void Menu2::setMbtn(std::unordered_map<std::string,std::string> list){
    for(auto &t : list){
        if (t.first == " "){
            break;
        }
        std::string msgInfo = t.second.c_str();
        std::string sender;
        std::string recver;
        std::string msg = msgInfo.substr(18);
        for(int i = 0; i < 9; i++){
            sender.push_back(msgInfo[i]);
            recver.push_back(msgInfo[i+9]);
        }
        if(sender == id){
            // if(std::find(vector.begin(), vector.end(),))
        }
    }
}

void Menu2::setFbtn(std::unordered_map<std::string,std::string> list){

    // QVector<QToolButton*> vector;
    QVBoxLayout *layout = new QVBoxLayout();
    qStack = new QStackedWidget();
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

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);// 设置按钮样式为文字紧贴图片
        // btn->setAutoRepeat(true)；
        layout->addWidget(btn);// 将按钮添加到布局
        this->vector.push_back(btn);
        FriendIsShow.push_back(false);
        // 添加聊天页面
        Widget *w = new Widget(nullptr, t.first.data(), fd);
        qStack->addWidget(w);
        ui->msgLayout->addWidget(qStack,0);
        lists.insert(std::pair<std::string, QToolButton*>(t.second, btn));
    }
    ui->listWidget->setLayout(layout);

    for(int i = 0; i < vector.count(); i++){
        connect(vector[i], &QToolButton::clicked,[this, i](){

            FriendIsShow[i] = true;
            qStack->setCurrentIndex(i); // 切换对话框
            ui->label->setText(this->vector[i]->text());
            qDebug() << "Button clicked:" << i << vector[i]->text();
        });
    }

}

   // 复制widget及其布局
QWidget* Menu2::copyWidget(QWidget* widget) {
    QWidget* newWidget = new QWidget();
    newWidget->setGeometry(widget->geometry());
    newWidget->setStyleSheet(widget->styleSheet());

    if (widget->layout()) {
        QVBoxLayout* layout = new QVBoxLayout();
        newWidget->setLayout(layout);

        for (int i = 0; i < widget->layout()->count(); ++i) {
            QWidget* originalChild = widget->layout()->itemAt(i)->widget();
            if (originalChild) {
                QWidget* newChild = copyWidget(originalChild);
                layout->addWidget(newChild);
            }
        }
    }

    return newWidget;
}

Menu2::~Menu2()
{
    delete ui;
}

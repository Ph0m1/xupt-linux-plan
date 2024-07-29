#include "menu2.h"
#include "ui_menu2.h"
#include "mysocket.h"
#include "widget.h"
#include "msgtype.h"
#include <QPainter>
#include <QToolButton>
#include <QPainterPath>
using json = nlohmann::json;

Menu2::Menu2(QWidget *parent, int sfd, const std::string& data)
    : QWidget(parent)
    , fd(sfd)
    , ui(new Ui::Menu2)
    ,threadPool(new ThreadPool(4))
    ,pauseThread(false)
{
    // 注册常用类型
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");
    qRegisterMetaType<std::unordered_map<std::string, std::string>>("std::unordered_map<std::string, std::string>");

    //解析data数据包
    std::cout<<data<<std::endl;
    json datajs = json::parse(data.data());

    json infojs = datajs["Info"].get<json>();
    //fl id:name
    //ml time(15位):<发送方id(9位)><接受方id(9位)><内容>

    std::unordered_map<std::string,std::string> fl = datajs["FriendList"].get<std::unordered_map<std::string,std::string>>();
    qDebug()<<"12";
    std::unordered_map<std::string,std::string> gl = datajs["GroupList"].get<std::unordered_map<std::string,std::string>>();
    std::unordered_map<std::string,std::string> ml = datajs["MsgList"].get<std::unordered_map<std::string,std::string>>();

    m_name = infojs["username"].get<std::string>();
    qDebug() << m_name.c_str();
    std::string id;

    id = datajs["Uid"].get<std::string>();
    qDebug() << id.c_str();
    this->m_id = id;
    ui->setupUi(this);

    // 设置图标
    this->setWindowIcon(QIcon("/Header/Header.jpeg"));

    // 设置名称
    this->setWindowTitle("Rooms");

    // 加载图像
    QPixmap pixmap(":/Header/Header.jpeg");

    if (pixmap.isNull()) {
        qDebug() << "Failed to load pixmap.";
        return;
    }
    // 裁剪成圆形
    QPixmap circularPixmap(pixmap.size());
    circularPixmap.fill(Qt::transparent);

    {
        QPainter painter(&circularPixmap);
        if (!painter.isActive()) {
            qDebug() << "Failed to create QPainter.";
            return;
        }
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        QPainterPath path1;
        path1.addEllipse(0, 0, pixmap.width(), pixmap.height());
        painter.setClipPath(path1);
        painter.drawPixmap(0, 0, pixmap);
        painter.end();
    }
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

    connect(ui->addBtn, &QToolButton::clicked,[=](){
        std::string line = ui->searchEdit->text().toStdString();
        if(line.empty()){
            QMessageBox::warning(this,"错误！","输入不能为空!");
            return;
        }
        sendMsg(fd,FriendAdd,line);

    });

    // 绑定信号和槽
    connect(this, SIGNAL(friendsg(std::string)), this,  SLOT(friendAdd(std::string)));
    connect(this, SIGNAL(refreshFriendList(std::string)),
            this, SLOT(updateFriendList(std::string)));
    connect(this, SIGNAL(refreshMsgList(std::string)),
            this, SLOT(upadteMsgList(std::string)));

    // 启动线程池
    threadPool->init();

    // 启动一个线程来接收服务器消息
    threadPool->submit([this] { readFromServer(this->fd); });
    // readFromServer(fd);
}

void Menu2::pauseMsgThread(){
    std::unique_lock<std::mutex> lock(pauseMutex);
    pauseThread = true;
    pauseCondition.wait(lock, [this] { return !pauseThread; });
}
void Menu2::resumeMsgThread() {
    {
        std::unique_lock<std::mutex> lock(pauseMutex);
        pauseThread = false;
    }
    pauseCondition.notify_one();
}

void Menu2::readFromServer(int fd){
    std::string buffer;
    while(true){
        // std::unique_lock<std::mutex> lock(pauseMutex);
        // pauseCondition.wait(lock, [this] { return !pauseThread; });
        try
        {
            MsgType type = recvMsg(fd,buffer);
            switch (type){
            case Msg:
                printmsg(buffer);
                break;
            case ReFreshFriendList:
                emit refreshFriendList(buffer);
                break;
            case FriendAdd:
                emit friendsg(buffer);
                break;

            }
        }
        catch(...){

        }
    }
}

void Menu2::updateFriendList(std::string msg){

}

void Menu2::friendAdd(std::string msg){
    Json js = Json::parse(msg.data());
    MsgType status = js["Status"].get<MsgType>();
    std::string res = js["Msg"].get<std::string>();
    qDebug() << res.c_str();
    if(status == Failure){
        QMessageBox::warning(this,"错误！",res.c_str());
        return;
    }
    if(status == Success){
        QMessageBox::information(this, "提示", res.c_str());
        return;
    }
    QMessageBox::information(this, "提示", "已发送好友请求！");
}

void Menu2::printmsg(std::string msg){
    emit sendData(msg);// 向聊天窗口发出信号
}
void Menu2::setMbtn(std::unordered_map<std::string,std::string> list){
    // QVBoxLayout *layout = new QVBoxLayout();
    for(auto &t : list){
        if (t.first == " "){
            break;
        }
        std::string msgInfo = t.second.c_str();
        std::string sender = msgInfo.substr(0,9);
        std::string recver = msgInfo.substr(9,9);
        std::string msg = msgInfo.substr(18);

        // 获取flag 1为消息，2为通知
        int flag = 1;
        if(sender == this->m_id){
            flag = 2;
        }
        if(sender != this->m_id && recver != this->m_id){
            flag = 3;
        }
        std::string key = sender == this->m_id ? recver : sender;
        msglist.push_front(lists[recver]);

        auto it = std::find(vector.begin(),vector.end(),lists[recver]);
        if(it == vector.end()){
            return;
        }
        int index = std::distance(vector.begin(), it); // 拿到下标
        qDebug() << "New msg form index: " << index << (*it)->text();

        // Widget *currentWidget = qStack->widget(index);
        // printmsg(key, msg, flag, currentWidget);
    }
}

void Menu2::setFbtn(std::unordered_map<std::string,std::string> list){

    // QVector<QToolButton*> vector;
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

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);// 设置按钮样式为文字紧贴图片
        // btn->setAutoRepeat(true)；
        layout->addWidget(btn);// 将按钮添加到布局
        this->vector.push_back(btn);
        FriendIsShow.push_back(false);
        // 添加聊天页面
        Widget *w = new Widget(nullptr, t.second.data(), t.first.data(), m_name.data(), m_id.data(), fd);
        connect(this,SIGNAL(sendData(std::string)),w,SLOT(getData(std::string)));
        qStack->addWidget(w);
        ui->msgLayout->addWidget(qStack,0);
        lists.insert(std::pair<std::string, QToolButton*>(t.second, btn));
    }
    // listStack->addWidget(layout->widget());
    // listStack->addItem(layout);
    ui->listLayout->insertLayout(0,layout);
    // ui->listWidget->setLayout(layout);


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
    // 确保删除所有动态分配的对象
    for (auto &btn : vector) {
        delete btn;
    }
    vector.clear();

    // 清理qStack中的页面
    while (qStack->count() > 0) {
        QWidget *w = qStack->widget(0);
        qStack->removeWidget(w);
        delete w;
    }

    // 删除qStack
    delete qStack;
    // close(fd);
    sendMsg(fd,Logout,"1");
    delete ui;
}

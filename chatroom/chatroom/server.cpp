#include "redis.h"
#include "mysocket.h"
#include "msgtype.h"
#include "server.h"
#include "smtpmailer.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
using json = nlohmann::json;
int main() {
    Server server;
    server.init();
    server.run();
    return 0;
}


void Server::handleClient(int client_fd) {
        std::string message;
        MsgType msgType = recvMsg(client_fd, message);
        if (msgType == Failure) {
            // 客户端断开连接
            close(client_fd);
            std::cout<<message<<std::endl;
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
            clients.erase(client_fd);
            std::cout << "Client disconnected: " << client_fd << std::endl;
        } else {
            // 处理收到的消息
            handleMessage(client_fd, msgType, message);
        }
    }

void Server::handleMessage(int fd, MsgType type, const std::string &msg) {
        // 根据消息类型进行处理
        switch (type) {
        case Disconnent:
            // 客户端断开连接
            close(fd);
            std::cout<<msg<<std::endl;
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
            clients.erase(fd);
            std::cout << "Client disconnected: " << fd << std::endl;
            break;
        case UserAccount:
            std::cout << "User Register message:" << msg << std::endl;
            reg(fd,msg);
            break;
        case UserLogin:
            std::cout << "User login message: " << msg << std::endl;
            login(fd,msg);
            break;
        case OutLine:
            std::cout << "User logout : " << msg << std::endl;
            logout(msg);
            break;
        case AccountFound:
            std::cout << "User found message: " << msg << std::endl;
            foundAccount(fd,msg);
            break;
        case Captcha:
            captcha(fd);
            break;
        // case ResetInfo:
        //     std::cout << "User reset infomation message: " << msg << std::endl;
        //     infoReset(fd,msg);
        //     break;
        // case AccountDelete:
        //     std::cout << "User delete account: " << msg << std::endl;
        //     deleteAccount(fd,msg);
        //     break;
        // case GroupCreat:
        //     std::cout << "User creat group message: " << msg << std::endl;
        //     creatGroup(fd,msg);
        //     break;
        // case GroupJoin:
        //     joinGroup(fd,msg);
        //     break;
        // case GroupExit:
        //     exitGroup(fd,msg);
        //     break;
        // case UserEnter:
        //     enter(fd,msg);
        //     break;
        // case UserLeft:
        //     left(fd,msg);
        //     break;
        // case Msg:
        //     Message(fd,msg);
        //     break;
        // case File:
        //     files(fd,msg);
        //     break;
        // case FriendAdd:
        //     addFriend(fd,msg);
        //     break;
        // case FriendDelete:
        //     deleteFriend(fd,msg);
        //     break;
        // case FriendBanned:
        //     bannedFriend(fd,msg);
        //     break;

        default:
            std::cout << "Unknown message type: " << type << std::endl;
            break;
        }
    }


void Server::broadcastMessage(int sender_fd, const std::string &message) {
        for (const auto &client : clients) {
            if (client.first != sender_fd) {
                sendMsg(client.first, Msg, message);
            }
        }
}

// 生成uid
std::string Server::generateUid(){
        std::srand(static_cast<unsigned int>(std::time(0)));
        std::ostringstream idStream;
        int a = rand() % 9 + 1;
        idStream<<a;
        for (int i = 1; i < 9; ++i) {
            int digit = rand() % 10; // 生成0到9之间的随机数
            idStream << digit;
        }
        Redis redis;
        std::string b = "UidSet";
        if(redis.Sismember(b,idStream.str())){
            return generateUid();
        }
        return idStream.str();
}



void Server::logout(std::string id){
    Redis r;
    r.Srem("Online",id);
}

void Server::reg(int fd, std::string str){
    std::string uid = generateUid();
    nlohmann::json js = nlohmann::json::parse(str);
    std::string name = js["username"];
    std::string mail = js["mail"];

    Redis redis;
    std::string cmd,cmd1,cmd2;
    cmd1 = UsernameHash" " + name;
    cmd2 = EmailHash" " + mail;
    if(redis.Hget(cmd1)){
        sendMsg(fd,Refuse,"该用户名已注册");
        return;
    }else if(redis.Hget(cmd2)){
        sendMsg(fd,Refuse,"该邮箱已注册");
        return;
    }
    redis.Hmset(cmd1,uid);
    redis.Hmset(cmd2,uid);
    cmd = UserInfo" " + uid;
    redis.Hmset(cmd,str);

    redis.Sadd(UidSet,uid);

    sendMsg(fd,Success,uid);
}
void Server::login(int fd,std::string str){
    nlohmann::json js = nlohmann::json::parse(str.data());

    std::string id = js["id"].get<std::string>();
    std::string passwd = js["passwd"].get<std::string>();
    Redis r;
    std::string uid = r.Hget(EmailHash,id);
    std::cout<<uid<<std::endl;
    std::cout<<"1"<<std::endl;
    if(uid != ""){
        id = uid;
    }
    std::string info = r.Hget(UserInfo,id);
    std::cout<<"2"<<std::endl;
    js = nlohmann::json::parse(r.Hget(UserInfo,id));
    std::cout<<"3"<<std::endl;
    if(!(js["passwd"] == passwd)){
        sendMsg(fd, Refuse,"帐号或密码错误");
        return;
    }

    users[fd] = id;
    //发送个人信息

    //json
    // Info: json
    // Msglist: map
    // Friendlist: map
    // Gruoplist: map
    std::cout<<"4"<<std::endl;
    json rec;
    rec["FriendList"] = getFl(id);
    rec["GroupList"]= getGl(id);
    rec["MsgList"] = getMl(id);
    rec["Info"] = js;
    std::string data = rec.dump();
    sendMsg(fd,Success,data);
    r.Sadd("Online", id);
}
void Server::foundAccount(int fd,std::string str){
    SMTPMailer mailer;
    std::string from = "<ph0m_hu.xa@foxmail.com>";
    std::vector<std::string> to = {"<" + str + ">"};
    std::string subject = "验证码";
    std::string c = mailer.getcode();
    std::string body = "您的验证码是: " + c;
    capts[fd] = c;
    if(mailer.sendMail(from, to, subject,body)){
        sendMsg(fd,Success);
    }else {
        sendMsg(fd,MailError);
    }
    found_queue[fd] = str;
}

void Server::captcha(int fd,std::string buf){

    if (buf.data() == capts[fd].data()){
        sendMsg(fd,Success);
    }
    else{
        sendMsg(fd,Refuse,"验证码错误！");
        return;
    }
}

void Server::resetpasswd(int fd, std::string str){
    Redis r;
    std::string mail = found_queue[fd];
    std::string id = r.Hget(EmailHash,mail);
    json infojs = json::parse(r.Hget(UserInfo,id).c_str());
    infojs["passwd"] = str;
    std::string a = infojs.dump();
    r.Hmset(UserInfo, a);
    sendMsg(fd,Success);
}

void Server::infoReset(int fd,std::string str){

}
void deleteAccount(int fd,std::string str);

void creatGroup(int fd, std::string str);
void joinGroup(int fd, std::string str);
void exitGroup(int fd, std::string str);

void enter(int fd, std::string str);
void left(int fd, std::string str);

void Message(int fd, std::string str);
void files(int fd, std::string str);

void addFriend(int fd, std::string str){

}
void deleteFriend(int fd, std::string str);
void bannedFriend(int fd, std::string str);


std::unordered_map<std::string,std::string> getFl(const std::string &key){
    std::string str = key + "f";
    Redis redis;
    std::unordered_map<std::string,std::string> list = redis.Hmget(str);

    return list;
}
std::unordered_map<std::string,std::string> getGl(const std::string &key){
    std::string str = key + "g";
    Redis redis;

    std::unordered_map<std::string,std::string> list = redis.Hmget(str);

    return list;
}
std::unordered_map<std::string,std::string> getMl(const std::string &key){
    std::string str = key + "m";
    Redis redis;
    std::unordered_map<std::string,std::string> list = redis.Hmget(str);

    return list;
}


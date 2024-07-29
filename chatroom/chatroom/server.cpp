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
        try{
        std::string message;
        MsgType msgType = recvMsg(client_fd, message);
        if (msgType == Failure || msgType == Disconnent) {
            // 客户端断开连接
            onlinelist.erase(users[client_fd]);
            users.erase(client_fd);
            close(client_fd);
            std::cout<<message<<std::endl;
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
            clients.erase(client_fd);
            std::cout << "Client disconnected: " << client_fd << std::endl; 
        } else {
            // 处理收到的消息
            handleMessage(client_fd, msgType, message);
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = client_fd;
            if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                perror("11epoll_ctl: client_fd");
            }
        }
        }catch(const std::exception &e){
            std::cerr << "Expection in handleClient: " << e.what() << std::endl;
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
            close(client_fd);
        }
    }

void Server::handleMessage(int fd, MsgType type, const std::string &msg) {
        // 根据消息类型进行处理
        switch (type) {
        case Disconnent:
            // 客户端断开连接
            onlinelist.erase(users[fd]);
            users.erase(fd);
            close(fd);
            std::cout<<msg<<std::endl;
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
            clients.erase(fd);
            if(onlinelist.find(users[fd]) != onlinelist.end()){
                onlinelist.erase(users[fd]);
            }
            users.erase(fd);
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
            captcha(fd,msg);
            break;
        case ResetPasswd:
            resetpasswd(fd,msg);
            break;
        // case ResetInfo:
        //     std::cout << "User reset infomation message: " << msg << std::endl;
        //     infoReset(fd,msg);
        //     break;
        case AccountDelete:
            std::cout << "User delete account: " << msg << std::endl;
            deleteAccount(fd,msg);
            break;
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
        case Msg:
            Message(fd,msg);
            break;
        // case File:fd
        //     files(fd,msg);
        //     break;
        case FriendAdd:
            std::cout << "User add frined: "<< msg << std::endl;
            addFriend(fd,msg);
            break;
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
    users.erase(onlinelist[id]);
    onlinelist.erase(id);
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

    accountInit(uid);

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
    if (info == ""){
        sendMsg(fd,Refuse,"该账户不存在");
    }
    std::cout<<"2"<<std::endl;
    js = nlohmann::json::parse(r.Hget(UserInfo,id));
    std::cout<<"3"<<std::endl;
    if(!(js["passwd"] == passwd)){
        sendMsg(fd,Refuse,"帐号或密码错误");
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
    rec["Uid"] = uid;
    rec["FriendList"] = getFl(id);
    rec["GroupList"]= getGl(id);
    rec["MsgList"] = getMl(id);
    rec["Info"] = js;
    std::string data = rec.dump();
    sendMsg(fd,Success,data);
    onlinelist[uid] = fd;
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
void Server::accountInit(std::string str){
    std::cout<<"正在初始化账户"<<std::endl;
    std::string superid = "000000001";
    Redis r;
    std::string str1 = superid + str + "欢迎来到PH0M的聊天室!";
    r.Hmset(str+"m",sha256(str1) + " " + str1);

    r.Hmset(str+ "f",superid + " " + "小H");

    std::cout<<"账户初始化完成"<<std::endl;
}
void Server::captcha(int fd,std::string buf){

    if (buf == capts[fd]){
        if(users[fd].empty()){
           sendMsg(fd,Success,"12");
        }
        sendMsg(fd,Success,users[fd]);
    }
    else{
        sendMsg(fd,Refuse,"111");
        return;
    }
}

void Server::resetpasswd(int fd, std::string str){
    Redis r;
    std::string mail = found_queue[fd];
    std::string id = r.Hget(EmailHash,mail);
    std::cout<<id<<std::endl;
    json infojs = json::parse(r.Hget(UserInfo,id).c_str());
    infojs["passwd"] = str;

    std::string a = infojs.dump();
    std::cout<<a<<std::endl;
    r.Hmset(UserInfo" "+ id, a);
    found_queue.erase(fd);
    sendMsg(fd,Success,"11");
}

void Server::infoReset(int fd,std::string str){

}
void Server::deleteAccount(int fd,std::string str){
    Redis r;
    std::string Info;
    Info = r.Hget(UserInfo,str);
    if(Info == ""){
        sendMsg(fd,Refuse);
        return;
    }
    json ijs = json::parse(Info);
    std::string username = ijs["username"].get<std::string>();
    std::string mail = ijs["username"].get<std::string>();
    std::string id = r.Hget(EmailHash,mail);
    r.Hdel(EmailHash,mail);
    r.Hdel(UserInfo,id);
    r.Srem(UidSet,id);
    // ...
    // 删除信息

    sendMsg(fd,Success);
}

void creatGroup(int fd, std::string str);
void joinGroup(int fd, std::string str);
void exitGroup(int fd, std::string str);

void enter(int fd, std::string str);
void left(int fd, std::string str);

void Server::Message(int fd, std::string str){
    Json js = json::parse(str);
    std::string time = js["Time"].get<std::string>();
    std::string msg = js["Msg"].get<std::string>();
    std::string sender = msg.substr(0,9);
    std::string recver = msg.substr(9,9);
    js["Status"] = Unread;
    std::string data = js.dump();
    std::string hash = sha256(str);
    Redis r;
    r.Hmset(sender + "m", hash + " " + data);
    r.Hmset(recver + "m", hash + " " + data);
    if(onlinelist.find(recver) != onlinelist.end()){
        sendMsg(onlinelist[recver],Msg,data);
    }

}
// 哈系函数
std::string Server::sha256(const std::string& str) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new(); //创建一个新的 EVP_MD_CTX 对象
    if(mdctx == nullptr){
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }
    if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr))
    {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to initialize EVP_DigestInit_ex");
    }
    // 更新哈希上下文，传递要哈希的字符串
    if(1 != EVP_DigestUpdate(mdctx, str.c_str(), str.length()))
    {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to update EVP_DigestUpdate");
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    // 完成哈希计算并获取结果
    if(1 != EVP_DigestFinal_ex(mdctx, hash, &len)){
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to finalize digest");
    }
    //  释放上下文
    EVP_MD_CTX_free(mdctx);
    // 将哈希结果转换为十六进制字符串
    std::stringstream ss;
    for(unsigned int i = 0; i < len; ++i){
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}
void files(int fd, std::string str);

void Server::addFriend(int fd, std::string str){
    Redis r;
    std::string uid = r.Hget(EmailHash,str);
    std::cout << str.c_str() <<"  " <<uid.c_str() << std::endl;
    if(uid == ""){
        uid = str;
    }
    if(!r.Sismember("UidSet",uid) || uid == ""){
        Json js;
        js["Msg"] = "该用户不存在";
        js["Status"] = Failure;
        std::string data = js.dump();
        sendMsg(fd,FriendAdd,data);
        return;
    }
    std::string mid = users[fd];
    std::string uname = getusername(uid);
    std::string mname = getusername(mid);
    std::cout << mid <<" " << mname << std::endl;
    std::cout << uid << " " << uname <<std::endl;
    if(r.Sismember(mid+"000",uid )){
        r.Hmset(mid + "f",uid+ " " + uname);
        r.Hmset(uid + "f",mid+ " " + mname);
        Json js;
        js["Msg"] = "已成功添加" + uname +"<" + uid + ">为好友！";
        js["Status"] = Success;
        std::string data = js.dump();
        sendMsg(fd,FriendAdd,data);
        r.Srem(mid+"000", mid);

        return;
    }
    if(onlinelist.count(uid)){
        sendMsg(onlinelist[uid], FriendAddMsg, mid);
    }
    Json js;
    js["Msg"] = "已向" + uname +"<" + uid + "> 发送好友请求！";
    js["Status"] = Success;
    std::string data = js.dump();
    sendMsg(fd,FriendAdd,data);
    std::string key = uid+"000";
    r.Sadd(key,mid);
}

void Server::acceptAddFrined(int fd, std::string str){

    std::string uid = str;
    std::string mid = users[fd];
    std::string uname = getusername(uid);
    std::string mname = getusername(mid);
    Redis r;
    if(!r.Sismember(mid+"000",uid)){
        sendMsg(fd,Refuse,"111");
        return;
    }
    r.Srem(mid+"000",uid);
    r.Hmset(mid + "f", uid + " " + uname);
    r.Hmset(uid + "f", mid + " " + mname);

    std::unordered_map<std::string, std::string> mf = getFl(mid);
    Json flist;
    flist["FriendList"] = mf;
    std::string data = flist.dump();
    sendMsg(fd,ReFreshFriendList,data);
}
void deleteFriend(int fd, std::string str);
void bannedFriend(int fd, std::string str);

std::string Server::getusername(std::string uid){
    Redis r;
    std::string info = r.Hget(UserInfo,uid);
    Json js = Json::parse(info.data());
    std::string uname = js["username"].get<std::string>();
    return uname;
}

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


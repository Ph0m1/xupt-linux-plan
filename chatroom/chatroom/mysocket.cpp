#include "mysocket.h"

void sendMsg(int sfd,MsgType type,const std::string &msg){
    nlohmann::json js;
    js["MsgType"] = type;
    js["Msg"] = msg;
    std::string data = js.dump();
    uint32_t len = data.size();
    send(sfd,data.c_str(),len,0);
}

void sendMsg(int sfd,MsgType type){

    send(sfd,&type,sizeof(type),0);
}
MsgType recvMsg(int sfd,std::string &str){

    char buffer[4096];
    int valread = read(sfd,buffer,sizeof(buffer));
    if (valread > 0) {
        nlohmann::json js = nlohmann::json::parse(buffer);
        std::memset(buffer,0,4096);
        str = js["Msg"];
        MsgType t = js["MsgType"];
        std::cout<<str<<std::endl;
        std::cout<<t<<std::endl;
        return t;
    }
    return Failure;
}
MsgType recvMsg(int sfd){
    MsgType a;
    int valread = read(sfd,&a,sizeof(a));
    if (valread > 0){
        return a;
    }
    return Failure;
}

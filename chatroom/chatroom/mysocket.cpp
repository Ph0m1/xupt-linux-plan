#include "mysocket.h"

void sendMsg(int fd,MsgType type){
    send(fd,&type,sizeof(type),0);
}

MsgType recvMsg(int sfd){
    MsgType a;
    int valread = read(sfd,&a,sizeof(a));
    if (valread >= 0){
        return a;
    }
    return Failure;
}

void sendMsg(int sfd,MsgType type,const std::string &msg){


    std::cout << "sendMsg started" << std::endl;

    if (sfd == -1 || msg.empty()) {
        std::cout << "Invalid socket or empty message" << std::endl;
        return;
    }
    std::cout << "Preparing JSON" << std::endl;
    nlohmann::json js;
    js["MsgType"] = type;
    js["Msg"] = msg;
    std::string data = js.dump();

    std::cout << "JSON prepared: " << data << std::endl;
    int len = htonl(data.size());
    std::string buf(4 + data.size(), '\0');

    memcpy(&buf[0], &len, 4);
    memcpy(&buf[4], data.data(), data.size());

    std::cout << "Buffer prepared, sending message" << std::endl;
    int ret = writen(sfd, buf, buf.size());
    if (ret < 0) {
        std::cerr << "Writing error" << std::endl;
        close(sfd);
    }
    std::cout << "sendMsg finished" << std::endl;
}


int writen(int fd,std::string buf, int len){
    const char *p = buf.c_str();
    int count = len;
    while(count > 0){
        int ret = send(fd, p ,count,0);
        if(ret <= -1){
            if(errno == EINTR && ret == -1){
                continue;
            }
            else
            {
                std::cerr << "Error sending data: "<<strerror(errno) << std::endl;
                return -1;
            }
        }
        else if(ret == 0){
            continue;
        }
        p +=ret;
        count -= ret;
    }
    return len;
}


MsgType recvMsg(int sfd,std::string &str){


    int len = 0;
    read(sfd,&len,4);
    len = ntohl(len);
    std::vector<char> buf(len+1);
    int ret = readen(sfd,buf.data(), len);
    if(ret == 0){
        return Disconnent;
    }
    else if( len != ret){
        return Failure;
    }
    buf[len] = '\0';
    nlohmann::json js = nlohmann::json::parse(buf.data());
    str.append(js["Msg"].get<std::string>());
    if (ret > 0)
        return js["MsgType"].get<MsgType>();
    return Failure;
}




int readen(int fd, char* buf, int len){
    int count = len;
    char *current = buf;
    while(count > 0 ){
        int ret = recv(fd,current,count,0);
        if(ret <= -1){
            if(errno == EINTR && ret == -1){
                continue;
            }else{
                std::cerr<< "Error receiving data: " << strerror(errno) << std::endl;
                close(fd);
                return -1;
            }
        }
        else if(ret == 0){
            break;
        }

        current += ret;
        count -= ret ;
    }
    return len-count;
}



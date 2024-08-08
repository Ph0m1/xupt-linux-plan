#ifndef MYSOCKET_H
#define MYSOCKET_H
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include "msgtype.h"
#define S_PORT 9098
#define C_PORT 9098
#define IP "127.0.0.1"

using Json = nlohmann::json;

const int MAX_LINK = 10;
MsgType recvMsg(int sfd);
void sendMsg(int fd,MsgType type);
std::string getInfo();
void sendMsg(int sfd,MsgType type,const std::string &msg);
MsgType recvMsg(int sfd,std::string &str);

void sendFile(int sfd, const std::string &filePath);
int writen(int fd, std::string buf, int len);
int readen(int fd, char* buf, int len);


#endif // MYSOCKET_H

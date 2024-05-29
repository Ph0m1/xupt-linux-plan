#ifndef MYSOCKET_H
#define MYSOCKET_H
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include "msgtype.h"
#define S_PORT 7000
#define C_PORT 7000
#define IP "127.0.0.1"

const int MAX_LINK = 100;

std::string getInfo();
void sendMsg(int sfd,MsgType type);
void sendMsg(int sfd,MsgType type,const std::string &msg);
MsgType recvMsg(int sfd,std::string &str);
MsgType recvMsg(int sfd);
#endif // MYSOCKET_H

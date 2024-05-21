#ifndef SVR_HPP
#define SVR_HPP
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define SVR_PORT 7000
#define SVR_IP "127.0.0.1"

// 最大同时链接数
const int MAX_LINK = 100;

#endif
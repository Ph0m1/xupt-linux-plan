// #include "json.hpp"
// #include "threadpool.hpp"
// #include "redis.hpp"
#include <iostream>

// #include "../../include/redis.hpp"
#include "../../include/threadpool.hpp"

#include <fcntl.h>
#include <netinet/in.h>
// #include "../../include/svr.hpp"
#include "svr.hpp"

#define MAX_EVENTS 10
#define BUF_SIZE 1024

int main() {
  //
  int svr_fd, new_sock, epoll_fd;
  struct sockaddr_in svrAddr;
  int svrAddrlen = sizeof(svrAddr);
  char buffer[BUF_SIZE];
  // 创建监听socket
  svr_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (svr_fd == -1) {
    perror("socket");
    exit(1);
  }
  // 设置isocket选项
  int opt = 1;
  setsockopt(svr_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // 绑定地址
  svrAddr.sin_family = AF_INET;
  svrAddr.sin_port = htons(PORT);
  svrAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(svr_fd, (struct sockaddr *)&svrAddr, sizeof(svrAddr)) == -1) {
    perror("bind");
    close(svr_fd);
    exit(1);
  }
  // 监听
  if (listen(svr_fd, 10) == -1) {
    perror("listen");
    close(svr_fd);
  }
  // 创建epoll实例
  epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    perror("epoll_create1");
    close(svr_fd);
    exit(1);
  }

  // 添加监听socket到epoll实例
  struct epoll_event event;
  event.data.fd = svr_fd;
  event.events = EPOLLIN;

  std::map<int, sockaddr_in> clients;

  // 创建线程池
  ThreadPool pool(4);

  // 创建Redis实例
//   Redis redis;

  // 创建epoll事件集
  struct epoll_event events[MAX_EVENTS];
  std::cout<<"Sever started"<<std::endl;

  std::cout<<"epoll_fd:"<<epoll_fd<<std::endl;
  std::cout<<"svr_fd:"<<svr_fd<<std::endl;
  std::cout<<"svrAddr:" << svrAddr.sin_addr.s_addr<<":" << svrAddr.sin_port<<std::endl;
  // 循环处理事件
  while (true) {
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    for (int i = 0; i < num_events; i++) {

      if (events[i].data.fd == svr_fd) {
        // 接受新的连接
        new_sock = accept(svr_fd, (struct sockaddr *)&svrAddr,
                          (socklen_t *)&svrAddrlen);
        if (new_sock == -1) {
          perror("accept");
          continue;
        }
        std::cout << "New connection: " << inet_ntoa(svrAddr.sin_addr) << ":"
                  << ntohs(svrAddr.sin_port) << std::endl;

        // 设置非阻塞模式
        int flags = fcntl(new_sock, F_GETFL, 0);
        fcntl(new_sock, F_SETFL, flags | O_NONBLOCK);

        // 添加新的socket到epoll实例
        event.data.fd = new_sock;
        event.events = EPOLLIN;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_sock, &event) == -1) {
          perror("epoll_ctl");
          close(new_sock);
          continue;
        }
        // 保存客户端地址信息
        clients[new_sock] = svrAddr;
      } else if (events[i].events & EPOLLIN) {
        // 读取客户端数据
        int sock = events[i].data.fd;
        ssize_t n = read(sock, buffer, BUF_SIZE);
        if (n == -1) {
          perror("read");
          close(sock);
          epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sock, NULL);
          clients.erase(sock);
          continue;
        } else if (n == 0) {
          // 客户端关闭连接
          std::cout << "Client disconnected: " << inet_ntoa(svrAddr.sin_addr)
                    << ":" << ntohs(svrAddr.sin_port) << std::endl;
          close(sock);
          epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sock, NULL);
          clients.erase(sock);
          continue;
        } else {
          //  打印并广播收到的消息
          std::cout << inet_ntoa(clients[sock].sin_addr)
                    << " message: " << buffer << std::endl;
          std::string message(buffer);
          pool.submit([&message, &clients, &sock]() {
            // 在Redis中存储消息
            // redis.Hmset(sock, message);
            // 向其他客户端广播消息
            for (auto &client : clients) {
              if (client.first != sock) {
                if (send(client.first, message.c_str(), message.length(), 0) ==
                    -1) {
                  std::cerr << "ERROE: send" << std::endl;
                  close(sock);
                  
                //   epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sock, nullptr);
                  clients.erase(sock);
                }
              }
            }
          });
        }
      }
    }
  }
}

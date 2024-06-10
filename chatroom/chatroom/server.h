#ifndef SERVER_H
#define SERVER_H
#include "redis.h"
#include "threadpool.h"
#include "mysocket.h"
#include "msgtype.h"
#include <curl/curl.h>
#include <unordered_map>
#include <cstring>

#define UsernameHash "UsernameSet"
#define UserInfo "UserInfo"
#define UidSet "UidSet"
#define EmailHash "EmailHash"
#define OnlineSet "OnlineSet"


class Server {
private:
    int server_fd;
    struct sockaddr_in server_addr;
    std::unordered_map<int, struct sockaddr_in> clients;
    ThreadPool threadPool;
    int epoll_fd;
    struct epoll_event ev, events[MAX_LINK];

    // 绑定fd和用户
    std::unordered_map<int, std::string> users;
    // 绑定fd和验证码
    std::unordered_map<int,std::string> capts;
    // 设置找回队列
    std::unordered_map<int ,std::string> found_queue;
private:
    void handleClient(int client_fd);

    void handleMessage(int client_fd, MsgType type, const std::string &message);

    void broadcastMessage(int sender_fd, const std::string &message);

    // 处理报文的函数
    void reg(int fd, std::string str);
    void login(int fd,std::string str);
    void foundAccount(int fd,std::string str);
    void infoReset(int fd,std::string str);
    void deleteAccount(int fd,std::string str);
    void resetpasswd(int fd,std::string str);
    void creatGroup(int fd, std::string str);
    void joinGroup(int fd, std::string str);
    void exitGroup(int fd, std::string str);

    void enter(int fd, std::string str);
    void left(int fd, std::string str);

    void Message(int fd, std::string str);
    void files(int fd, std::string str);

    void addFriend(int fd, std::string str);
    void deleteFriend(int fd, std::string str);
    void bannedFriend(int fd, std::string str);

    void logout(std::string id);
    // 校验验证码
    void captcha(int fd, std::string str);


    // 生成uid
    std::string generateUid();
    // 设置为非阻塞
    int setNonBlocking(int fd) {
        int flags = fcntl(fd, F_GETFL, 0);
        if (flags == -1) {
            return -1;
        }
        return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    }

public:


    Server() : threadPool(10) {}

    void init() {

        // Redis redis;

        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(S_PORT);
        server_addr.sin_addr.s_addr = inet_addr(IP);

        if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("bind");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, MAX_LINK) == -1) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        epoll_fd = epoll_create1(0);
        if (epoll_fd == -1) {
            perror("epoll_create1");
            exit(EXIT_FAILURE);
        }

        ev.events = EPOLLIN;
        ev.data.fd = server_fd;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
            perror("epoll_ctl: server_fd");
            exit(EXIT_FAILURE);
        }

        threadPool.init();
        std::cout << "Chat server initialized." << std::endl;

    }

    void run() {
        while (true) {
            int nfds = epoll_wait(epoll_fd, events, MAX_LINK, -1);
            if (nfds == -1) {
                perror("epoll_wait");
                exit(EXIT_FAILURE);
            }

            for (int n = 0; n < nfds; ++n) {
                if (events[n].data.fd == server_fd) {
                    struct sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
                    if (client_fd == -1) {
                        perror("accept");
                        continue;
                    }

                    clients[client_fd] = client_addr;
                    ev.events = EPOLLIN | EPOLLET;
                    ev.data.fd = client_fd;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                        perror("epoll_ctl: client_fd");
                        exit(EXIT_FAILURE);
                    }

                    std::cout << "Client connected: " << client_fd << std::endl;
                } else {
                    int client_fd = events[n].data.fd;
                    threadPool.submit([this, client_fd]() {
                        setNonBlocking(client_fd);
                        std::cout<<"shdgasjd"<<std::endl;
                        handleClient(client_fd); });
                }
            }
        }
    }

    ~Server() {
        close(server_fd);
        close(epoll_fd);
    }
};
void sendFriendsList(int fd,std::string id);
std::unordered_map<std::string,std::string> getFl(const std::string &key);
std::unordered_map<std::string,std::string> getGl(const std::string &key);
std::unordered_map<std::string,std::string> getMl(const std::string &key);

#endif // SERVER_H

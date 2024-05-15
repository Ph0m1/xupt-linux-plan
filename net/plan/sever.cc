#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>

#define PORT 7000
int conn;

void thread_task(){

}
int main()
{
    std::cout << AF_INET << std::endl;
    std::cout << SOCK_STREAM << std::endl;
    std::cout << PORT << std::endl;
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in svr_addr;
    // 设置相关参数
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(PORT);
    svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sfd, (struct sockaddr*)&svr_addr, sizeof(svr_addr)) < 0){ //绑定socket地址及端口
        std::cout << "bind error" << std::endl;
        return -1;
    }
    if(listen(sfd, 5) < 0){ //阻塞监听
        std::cout << "listen error" << std::endl;
        return -1;
    }

    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    conn = accept(sfd, (struct sockaddr*)&cli_addr, &cli_len);
    if(conn<0){
        std::cout << "accept error" << std::endl;
        return -1;
    }
    char recvbuf[1024];
    char sendbuf[1024];
    while(1){
        memset(recvbuf, 0, sizeof(recvbuf));
        
        int len = recv(conn,recvbuf,sizeof(recvbuf),0);//接收
        if(strcmp(recvbuf, "exit") == 0){
            break;
        }
        std::cout << recvbuf << std::endl;
        send(conn, recvbuf, strlen(recvbuf), 0);
    }
    close(conn);
    close(sfd);
    return 0;
   
}
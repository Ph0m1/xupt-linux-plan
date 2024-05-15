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
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0){
        std::cout<<"socket error"<<std::endl;
        return -1;
    }
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(sfd,(struct sockaddr*)&addr,sizeof(addr)) < 0){ //链接服务端
        std::cout<<"connect error"<<std::endl;
        return -1;
    }
    char recvbuf[BUFFER_SIZE], sendbuf[BUFFER_SIZE];
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL){
        send(sfd, sendbuf,strlen(sendbuf),0);//发送
        if(strcmp(sendbuf,"exit\n") == 0){
            break;
        }
        recv(sfd, recvbuf, sizeof(recvbuf), 0);//接收
        fputs(recvbuf, stdout);
        memset(recvbuf, 0, sizeof(recvbuf));
        memset(sendbuf, 0, sizeof(sendbuf));
    }
    close(sfd);
    return 0;
}

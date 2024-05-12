#include "i6d_socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    struct sockaddr_in6 svaddr;
    int sfd, j;
    size_t msgLen;
    ssize_t numBytes;
    char resp[BUF_SIZE];

    if(argc < 3 || strcmp(argv[1], "--help") == 0){
        exit(1);
    }
    sfd = socket(AF_INET6,SOCK_DGRAM, 0);
    if(sfd == -1){
        perror("socket error");
        exit(1);
    }
    memset(&svaddr, 0, sizeof(struct sockaddr_in6));
    svaddr.sin6_family = AF_INET6;
    svaddr.sin6_port = htons(PORT_NUM);

    if(inet_pton(AF_INET6, argv[1], &svaddr.sin6_addr) <= 0){
        perror("inet_pathton error");
        exit(1);
    }
    
    //发送消息至服务器

    for(j = 2; j < argc; j++){
        msgLen = strlen(argv[j]);
        if(sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_in6)) != msgLen){
            perror("sendto error");
            exit(1);
        }

        numBytes = recv(sfd, resp, BUF_SIZE, 0);
        if(numBytes == -1){
            perror("recv error");
            exit(1);
        }
        printf("Response %d: %.*s\n", j - 1, (int )numBytes, resp);
    }

    exit(EXIT_SUCCESS);
}
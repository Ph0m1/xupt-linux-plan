#include "i6d_socket.h"

int main(int argc, char *argv[]) {
  struct sockaddr_in6 svaddr, claddr;
  int sfd, j;
  ssize_t numBytes;
  socklen_t len;
  char buf[BUF_SIZE];
  char claddrStr[INET6_ADDRSTRLEN];

  sfd = socket(AF_INET6, SOCK_DGRAM, 0);
  if (sfd == -1) {
    perror("socket");
    exit(1);
  }

  memset(&svaddr, 0, sizeof(struct sockaddr_in6));
  svaddr.sin6_family = AF_INET6;
  svaddr.sin6_port = htons(PORT_NUM);
  svaddr.sin6_addr = in6addr_any;

  if (bind(sfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_in6)) ==
      -1) {
    perror("bind");
    exit(1);
  }

  // 接受消息并在 客户端 返回
  while (1) {
    len = sizeof(struct sockaddr_in6);
    numBytes = recvfrom(sfd, buf,BUF_SIZE,0,(struct sockaddr *) &claddr, &len);
    if(numBytes == -1){
        perror("recvfrom");
        exit (1);
    }
    if(inet_ntop(AF_INET6, &claddr.sin6_addr, claddrStr, INET6_ADDRSTRLEN) == NULL){
        printf("Couldn't convert client address to string\n");
    }
    else {
        printf("Sever received %ld bytes from (%s, %u) \n", (long)numBytes, claddrStr, ntohs(claddr.sin6_port));
    }

    for(j = 0; j < numBytes; j++){
        buf[j] = toupper((unsigned char)buf[j]);
    }
    if(sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) != numBytes)
    {
        perror("sendto");
        // exit(1);
    }
  }

  return 0;
}
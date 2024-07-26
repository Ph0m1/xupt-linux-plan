#ifndef CLIENT_H
#define CLIENT_H

#include "msgtype.h"
#include "mysocket.h"
// #include <aes.h>
#include <openssl/aes.h>
#include <QWidget>


class Client
{
public:
    Client(int argc,char*argv[]);
    ~Client();

private:
    int m_sfd;
    // struct sockaddr_in m_addr;
    std::string key;

};

#endif // CLIENT_H

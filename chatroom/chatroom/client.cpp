#include "client.h"
#include "log.h"

Client::Client(int argc,char *argv[]) {
    this->m_sfd = socket(AF_INET,SOCK_STREAM,0);
    if(this->m_sfd<0){
        std::cout<<"Socket error!"<<std::endl;
        exit(-1);
    }
    memset(&this->m_addr,0,sizeof(this->m_addr));
    this->m_addr.sin_family = AF_INET;
    if(argc <= 1){
        this->m_addr.sin_port = htons(C_PORT);
        this->m_addr.sin_addr.s_addr = inet_addr(IP);
    }
    else if(argc >1){
        int port = atoi(argv[2]);
        this->m_addr.sin_port = htons(port);
        this->m_addr.sin_addr.s_addr = inet_addr(argv[1]);
    }
    if(connect(this->m_sfd,(struct sockaddr*)&this->m_addr,sizeof(this->m_addr)) < 0){ //链接服务端
        std::cout<<"connect error"<<std::endl;
        exit(-1);
    }
    std::cout <<"client started"<<std::endl;

    class log *ui = new class log(nullptr,this->m_sfd);
    ui->show();
}

Client::~Client(){
    sendMsg(this->m_sfd,Disconnent,"0");
}

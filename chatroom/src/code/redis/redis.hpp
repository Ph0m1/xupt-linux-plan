#ifndef _REDIS_HPP_
#define _REDIS_HPP_

#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
class Redis{
    public:
    Redis(){
        connect("127.0.0.1",6379);
        
        }
    ~Redis(){
        
    }
    bool connect(std::string host, int port){
        this->_connect = redisConnect(host.c_str(),port);
        if(this->_connect != NULL && this->_connect->err){
            std::cout<<"connect redis error"<<std::endl;
            return false;
        }
        return true;
    }

    std::string get(std::string key){
        this->_reply = (redisReply*)redisCommand(this->_connect,"GET %s",key.c_str());
        std::string str = this->_reply->str;
        freeReplyObject(this->_reply);
        return str;
    }

    void hset(std::string group,int key, std::string value){
        redisCommand(this->_connect, "HSET %s %d %s", group.c_str(),key,value.c_str());
    }

    void hdel(std::string key){
        redisCommand(this->_connect, "DEL %s", key.c_str());
    }
private:
    redisContext* _connect;
    redisReply* _reply;

};

#endif 
#ifndef _REDIS_HPP_
#define _REDIS_HPP_

#include "json.hpp"
#include <hiredis/hiredis.h>
#include <iostream>
#include <string>

#define IP "127.0.0.1"
#define PORT 6379

class Redis {
private:
  redisContext *m_context;
  redisReply *m_reply;
  std::string m_ip;
  int m_port;
  std::string m_json;

public:
  // 构造函数
  // 连接redis
  Redis(std::string json) {
    m_ip = IP;
    m_port = PORT;
    m_context = redisConnect(m_ip.c_str(), m_port);
    if (m_context == NULL || m_context->err) {
      if (m_context) {
        std::cout << "Error: " << m_context->errstr << std::endl;
        redisFree(m_context);
      }
      exit(1);
    }
    m_json = json;
  }
  // 析构函数
  ~Redis();

  bool Hmset(int key, std::string json);
  bool Hget(int key);
  bool Hdel(int key);
  bool Hmexists(int key, std::string value);
  bool Hmget(int key);
};

#endif
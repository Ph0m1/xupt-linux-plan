#include "redis.hpp"
// #include "redis.hpp"

bool Redis::Hmset(int key, std::string json) {
    std::string cmd = "HMSET " + std::to_string(key) + " " + json;
    m_reply = (redisReply *)redisCommand(m_context, cmd.c_str());
    if (m_reply->type == REDIS_REPLY_ERROR) {
      std::cout << "Error: " << m_reply->str << std::endl;
      return false;
    }
    return true;
  }
  bool Redis::Hget(int key) {
    std::string cmd = "HGET " + std::to_string(key);
    m_reply = (redisReply *)redisCommand(m_context, cmd.c_str());
    if (m_reply->type == REDIS_REPLY_ERROR) {
      std::cout << "Error: " << m_reply->str << std::endl;
      return false;
    }
    return true;
  }
  bool Redis::Hdel(int key) {
    std::string cmd = "HDEL " + std::to_string(key);
    m_reply = (redisReply *)redisCommand(m_context, cmd.c_str());
    if (m_reply->type == REDIS_REPLY_ERROR) {
      std::cout << "Error: " << m_reply->str << std::endl;
      return false;
    }
    return true;
  }
  bool Redis::Hmexists(int key, std::string value) {
    std::string cmd = "HMEXISTS " + std::to_string(key) + " " + value;
    m_reply = (redisReply *)redisCommand(m_context, cmd.c_str());
    if (m_reply->type == REDIS_REPLY_ERROR) {
      std::cout << "Error: " << m_reply->str << std::endl;
      return false;
    }
    return true;
  }
  bool Redis::Hmget(int key) {
    std::string cmd = "HGETALL " + std::to_string(key);
    m_reply = (redisReply *)redisCommand(m_context, cmd.c_str());
    if (m_reply->type == REDIS_REPLY_ERROR) {
      std::cout << "Error: " << m_reply->str << std::endl;
      return false;
    }
    return true;
  }
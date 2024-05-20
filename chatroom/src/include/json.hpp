#ifndef JSON_HPP
#define JSON_HPP

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#define JSON_BUF_SIZE 1024
#endif

class Json {
  rapidjson::Document doc;
  rapidjson::StringBuffer buffer;
  rapidjson::Value value;
  rapidjson::Writer<rapidjson::StringBuffer> writer;

public:
  Json(std::string json_string) { this->doc.SetObject(); }

  void add(std::string &key,
           std::string &value); // 向doc中添加键值对,无则添加，有则修改

  std::string toString(); // 返回json字符串

  void clear(); // 清空doc
    
  ~Json() {
    clear();
    // 释放内存
  }
};
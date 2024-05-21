#ifndef JSON_HPP
#define JSON_HPP

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#define JSON_BUF_SIZE 1024

class RapidJson {
  rapidjson::Document doc;
  rapidjson::StringBuffer buffer;
  rapidjson::Value m_value;
  rapidjson::Writer<rapidjson::StringBuffer> writer;

public:
  RapidJson() { this->doc.SetObject(); }

  void add(std::string &key,
           std::string &value); // 向doc中添加键值对,无则添加，有则修改

  std::string toString(); // 返回json字符串

  void clear(); // 清空doc

  // 重载"[]"
  // 向json中插入指定建的值
  void stdValue(std::string &key, std::string &value) {
    operator[](key, value);
  }
  // 向json中插入指定建的值
  void operator[](std::string &key, std::string value) { 
    doc[key] = value;
   }

  ~RapidJson() {
    clear();
    // 释放内存
  }
};
#endif
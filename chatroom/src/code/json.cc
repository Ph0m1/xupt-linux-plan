#include "json.hpp"


void Json::add(std::string &key, std::string &value) {  // 向doc中添加键值对,无则添加，有则修改

    for (rapidjson::Value::MemberIterator it = doc.MemberBegin(); it != doc.MemberEnd(); ++it) {
        if (it->name.GetString() == key) {
            it->value.SetString(value.c_str(), value.length(), doc.GetAllocator());
            return;
        }
    }

    doc.AddMember(rapidjson::Value(key.c_str(), key.length(), doc.GetAllocator()),
                  rapidjson::Value(value.c_str(), value.length(), doc.GetAllocator()), doc.GetAllocator());
  }

  std::string Json::toString() { // 返回json字符串
    writer.SetMaxDecimalPlaces(JSON_BUF_SIZE);
    this->doc.Accept(writer);
    return buffer.GetString();
  }
  void Json::clear() {
    // 清空doc
    doc.Clear();
    buffer.Clear();
    value.Clear();
  }
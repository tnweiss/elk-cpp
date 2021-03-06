//
// Created by tnwei on 1/9/2022.
//

#include "elk/common/model.h"


elk::Model::Model(const nlohmann::json &json):
  _json(std::make_shared<nlohmann::json>(json)),
  _basePointer(nlohmann::json::json_pointer("/")){
}

elk::Model::Model(const char *jsonString):
    _json(std::make_shared<nlohmann::json>(nlohmann::json::parse(jsonString))),
    _basePointer(nlohmann::json::json_pointer("/")) {

}

elk::Model::Model(const std::string &jsonString):
  _json(std::make_shared<nlohmann::json>(nlohmann::json::parse(jsonString))),
  _basePointer(nlohmann::json::json_pointer("/")){
}

elk::Model::Model(std::shared_ptr<nlohmann::json> json, nlohmann::json::json_pointer  basePointer):
  _json(std::move(json)), _basePointer(std::move(basePointer)) {
}

std::string elk::Model::get_string(const char *key) const {
  return _json->at(attr_pointer(key)).get<std::string>();
}

std::string elk::Model::get_string(const char *key, const char* defaultVal) const {
  return _json->value(attr_pointer(key), defaultVal);
}

int elk::Model::get_int(const char *key) const {
  return _json->at(attr_pointer(key)).get<int>();
}

long elk::Model::get_long(const char *key) const {
  return _json->at(attr_pointer(key)).get<long>();
}

int elk::Model::get_int(const char *key, const int defaultValue) {
  return _json->value(attr_pointer(key), defaultValue);
}

long elk::Model::get_long(const char *key, long defaultValue) {
  return _json->value(attr_pointer(key), defaultValue);
}

nlohmann::json::json_pointer elk::Model::attr_pointer(const char *key) const {
  spdlog::debug(std::string("Model::_basePointer(") + _basePointer.to_string() + ")");
  spdlog::debug(std::string("get_key(") + key + ")");

  // ensure base pointer ends with a /
  std::string str_json_ptr(_basePointer);
  if (str_json_ptr.empty() || str_json_ptr.at(str_json_ptr.size() - 1) != '/') {
    str_json_ptr += "/";
  }

  // ensure the key does not start with a '/'
  if (*key == '/') {
    str_json_ptr += (key + 1);
  } else {
    str_json_ptr += key;
  }

  nlohmann::json::json_pointer newPtr(str_json_ptr);

  spdlog::debug(std::string("newPtr(") + newPtr.to_string() + ")");
  spdlog::debug("");

  return newPtr;
}

elk::Model::Model(const elk::Model &model) = default;

elk::Model::Model(elk::Model &&model) noexcept: _basePointer(model._basePointer), _json(model._json){

}

void elk::Model::set(const char *key, std::string val) const {
  (*_json)[attr_pointer(key)] = val;
}

void elk::Model::set(const char *key, const char *val) const {
  (*_json)[attr_pointer(key)] = val;
}

void elk::Model::set(const char *key, int val) const {
  (*_json)[attr_pointer(key)] = val;
}

void elk::Model::set(const char *key, long val) const {
  (*_json)[attr_pointer(key)] = val;
}

void elk::Model::set(const char *key, bool val) const {
  (*_json)[attr_pointer(key)] = val;
}

void elk::Model::set(const char *key, elk::Model& val) const {
  (*_json)[attr_pointer(key)] = val._json->at(val._basePointer);
}

bool elk::Model::get_bool(const char *key) const {
  return _json->at(attr_pointer(key)).get<bool>();
}

bool elk::Model::get_bool(const char *key, bool defaultValue) {
  return _json->value(attr_pointer(key), defaultValue);
}

std::string elk::Model::to_string() const {
  return _json->dump();
}

std::string elk::Model::to_string(short indent) const {
  return _json->dump(indent);
}

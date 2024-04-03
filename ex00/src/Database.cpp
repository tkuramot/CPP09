//
// Created by tkuramot on 4/3/24.
//

#include "Database.hpp"
#include "utils.hpp"
#include <fstream>

Database::Database() {}

Database::Database(const std::string &key_value_delimiter)
    : key_value_delimiter_(key_value_delimiter) {
}

Database::Database(const Database &other)
    : key_value_delimiter_(other.key_value_delimiter_), data_(other.data_) {
}

Database &Database::operator=(const Database &other) {
  if (this != &other) {
    return *this;
  }
  key_value_delimiter_ = other.key_value_delimiter_;
  data_ = other.data_;
  return *this;
}

Database::~Database() {}

std::map<std::string, std::string> Database::GetData() const {
  return data_;
}

bool Database::Load(const std::string &file_path) {
  std::ifstream db_file(file_path.c_str());
  if (!db_file.is_open()) {
    return false;
  }

  std::string line;
  // discard the header
  std::getline(db_file, line);
  // read the key-value pairs
  while (std::getline(db_file, line)) {
    std::pair<std::string, std::string> key_value = SplitKeyValue(line, key_value_delimiter_);
    data_.insert(key_value);
  }
  return true;
}

// if the key is not found, return lower closest date
std::string Database::Find(const std::string &key) const {
  if (data_.empty()) {
    return "";
  }

  std::map<std::string, std::string>::const_iterator itr = data_.lower_bound(key);
  if (itr->first == key || itr == data_.begin()) {
    return itr->second;
  }
  std::advance(itr, -1);
  return itr->second;
}

//
// Created by tkuramot on 4/3/24.
//

#include "Database.hpp"
#include <fstream>
#include <iostream>

Database::Database() {}

Database::Database(const std::string &key_value_delimiter)
    : key_value_delimiter_(key_value_delimiter) {
}

Database::Database(const Database &other) {
  (void) other;
}

Database &Database::operator=(const Database &other) {
  (void) other;
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
    std::pair<std::string, std::string> key_value = ReadKeyValuePair(line);
    data_.insert(key_value);
  }
  return true;
}

std::pair<std::string, std::string> Database::ReadKeyValuePair(const std::string &line) {
  size_t delimiter_pos = line.find(key_value_delimiter_);
  if (delimiter_pos == std::string::npos) {
    return std::make_pair(line, "");
  }
  return std::make_pair(
      line.substr(0, delimiter_pos),
      line.substr(delimiter_pos + key_value_delimiter_.length() + 1)
  );
}

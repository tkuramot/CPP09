//
// Created by tkuramot on 4/3/24.
//

#ifndef BTC_SRC_DATABASE_HPP_
#define BTC_SRC_DATABASE_HPP_

#include <string>
#include <map>

class Database {
 public:
  // canonical form
  Database(const std::string &key_value_delimiter);
  Database(const Database &other);
  Database &operator=(const Database &other);
  ~Database();

  std::map<std::string, std::string> GetData() const;
  bool Load(const std::string &file_path);
  std::string Find(const std::string &key) const;

 private:
  std::string key_value_delimiter_;
  std::map<std::string, std::string> data_;

  Database();
};

#endif //BTC_SRC_DATABASE_HPP_

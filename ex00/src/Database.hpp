//
// Created by k.t. on 2024/02/15.
//

#ifndef BTC_EX00_INCLUDE_DATABASE_HPP_
#define BTC_EX00_INCLUDE_DATABASE_HPP_

#include <fstream>
#include <map>
#include <sstream>
#include <string>

class Database {
  Database(const Database &other);
  Database &operator=(const Database &other);
  ~Database();

  Database(const std::string &file_name);

  void LoadDatabase();
  template <typename F> void IterateOverRows(F func);
  static std::pair<std::string, double> ReadOneRecord(std::stringstream &row);

private:
  std::string file_name_;
  std::map<std::string, double> value_per_date_;
  const static int kMaxValue = 1000;

  // ファイル名の指定なしでインスタンス化する意味はないのでprivateにする
  Database();
  static bool IsValidDateFormat(std::string &date);
};

template <typename F> void Database::IterateOverRows(F func) {
  std::ifstream db_file(file_name_);

  // ヘッダは飛ばした上で、各行を読む
  std::string row;
  std::getline(db_file, row);
  while (std::getline(db_file, row)) {
    func(std::stringstream(row));
  }
}

#endif // BTC_EX00_INCLUDE_DATABASE_HPP_

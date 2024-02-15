//
// Created by k.t. on 2024/02/15.
//

#include "BitcoinDatabase.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

BitcoinDatabase::BitcoinDatabase() {}

BitcoinDatabase::BitcoinDatabase(const std::string &file_name)
    : file_name_(file_name) {
  LoadDatabase();
}

BitcoinDatabase::BitcoinDatabase(const BitcoinDatabase &other)
    : file_name_(other.file_name_) {}

BitcoinDatabase &BitcoinDatabase::operator=(const BitcoinDatabase &other) {
  if (this == &other) {
    return *this;
  }
  file_name_ = other.file_name_;
  return *this;
}

BitcoinDatabase::~BitcoinDatabase() {}

void BitcoinDatabase::LoadDatabase() {
}

std::pair<std::string, double>
BitcoinDatabase::ReadOneRecord(std::stringstream &row) {
  // 想定した型の読み込みに失敗した場合、ファイルからの回復不能な読み込みエラーが生じた場合に例外を投げる
  row.exceptions(std::ios::failbit | std::ios::badbit);

  std::string date;
  char _;
  double value;
  row >> date >> _ >> value;

  // 日付と値の範囲を検証する
  if (!IsValidDateFormat(date)) {
    std::cerr << "Error: bad input => " << date << '.' << std::endl;
  }
  if (value < 0) {
    std::cerr << "Error: not a positive number." << std::endl;
  }
  if (value > BitcoinDatabase::kMaxValue) {
    std::cerr << "Error: too large a number." << std::endl;
  }

  return std::pair<std::string, double>(date, value);
}

bool BitcoinDatabase::IsValidDateFormat(std::string &date) { return true; }
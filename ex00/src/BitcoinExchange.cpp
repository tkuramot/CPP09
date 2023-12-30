//
// Created by k.t. on 2023/12/17.
//

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : rates_(other.rates_) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other) {
    rates_ = other.rates_;
  }
  return *this;
}

BitcoinExchange::BitcoinExchange(std::string file_name) {
  ReadBitcoinPriceDatabase(file_name);
}

void BitcoinExchange::ReadBitcoinPriceDatabase(std::string &file_name) throw(
    std::runtime_error) {
  std::ifstream exchange_rate_csv(file_name);
  if (!exchange_rate_csv.is_open()) {
    throw std::runtime_error("Failed to open database file");
  }

  std::string buffer;
  // ヘッダをスキップ
  if (!std::getline(exchange_rate_csv, buffer)) {
    throw std::runtime_error(
        "Database file is empty or does not contain a header");
  }

  std::string time;
  double rate;
  while (std::getline(exchange_rate_csv, buffer)) {
    // 区切り文字を空白に置き換える
    std::string delimiter = ",";
    size_t pos = buffer.find(delimiter);
    if (pos != std::string::npos) {
      buffer.replace(pos, delimiter.size(), " ");
    }

    std::stringstream row(buffer);
    row.exceptions(std::stringstream::failbit);
    row >> time >> rate;
    rates_[time] = rate;
  }
}

void BitcoinExchange::ProcessInput(std::string &file_name) {
  std::ifstream exchange_rate_csv(file_name);
  if (!exchange_rate_csv.is_open()) {
    throw std::runtime_error("Error: could not open file.");
  }

  std::string buffer;
  // ヘッダをスキップ
  if (!std::getline(exchange_rate_csv, buffer)) {
    throw std::runtime_error(
        "Error: database file is empty or does not contain a header.");
  }

  std::string time, value;
  while (std::getline(exchange_rate_csv, buffer)) {
    // 区切り文字を空白に置き換える
    std::string delimiter = " | ";
    size_t pos = buffer.find(delimiter);
    if (pos != std::string::npos) {
      buffer.replace(pos, delimiter.size(), " ");
    }

    std::stringstream row(buffer);
    if (!IsValidDate(time)) {
      continue;
    }
    if (!IsValidValue(value)) {
      continue;
    }
    // process
  }
}

bool BitcoinExchange::IsValidDate(const std::string &date) {
  (void)date;
  return true;
}

bool BitcoinExchange::IsValidValue(const std::string &value) {
  (void)value;
  return true;
}
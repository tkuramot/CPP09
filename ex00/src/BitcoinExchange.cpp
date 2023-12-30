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
    size_t pos = buffer.find(',');
    if (pos != std::string::npos) {
      buffer.replace(pos, 1, " ");
    }
    std::stringstream row(buffer);
    if (!(row >> time >> rate)) {
      throw std::runtime_error("Failed to parse a line in database");
    }
    rates_[time] = rate;
  }
}

void BitcoinExchange::ProcessInput(std::string &file_name) {
  ReadInputDatabase(file_name);

  for (std::map<std::string, std::string>::iterator itr = input_db_.begin();
       itr != input_db_.end(); ++itr) {
    if (!IsValidDate(itr->first)) {
      continue;
    }
    if (!IsValidValue(itr->second)) {
      continue;
    }
  }
}

void BitcoinExchange::ReadInputDatabase(std::string &file_name) {
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
    size_t pos = buffer.find(" | ");
    if (pos != std::string::npos) {
      buffer.replace(pos, 1, " ");
    }
    std::stringstream row(buffer);
    if (!(row >> time >> value)) {
      throw std::runtime_error("Error: invalid data format.");
    }
    input_db_[time] = value;
  }
}

bool BitcoinExchange::IsValidDate(const std::string &data) {
}

bool BitcoinExchange::IsValidValue(const std::string &value) {
}
//
// Created by k.t. on 2023/12/17.
//

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

const std::string BitcoinExchange::kDatabaseFile = "./data.csv";

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

void BitcoinExchange::ReadExchangeRateDatabase() throw(
    std::runtime_error) {
  std::ifstream exchange_rate_csv(kDatabaseFile);
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
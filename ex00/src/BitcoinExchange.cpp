//
// Created by tkuramot on 4/3/24.
//

#include "BitcoinExchange.hpp"
#include <iostream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
  (void) other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  (void) other;
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::LoadExchangeRate(const std::string &filename) {
  if (!exchange_rate_.Load(filename)) {
    std::cerr << "Failed to open database file: " << filename << std::endl;
    return false;
  }
  return true;
}

void BitcoinExchange::SimulateExchange(const std::string &input_filename) {
  Database input;
  if (!input.Load(input_filename)) {
    std::cerr << "Failed to open input file: " << input_filename << std::endl;
    return;
  }
}

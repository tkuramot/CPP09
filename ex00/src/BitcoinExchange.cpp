//
// Created by tkuramot on 4/3/24.
//

#include "BitcoinExchange.hpp"
#include "utils.hpp"
#include <iostream>
#include <limits>
#include <fstream>

BitcoinExchange::BitcoinExchange() : exchange_rate_db_(",") {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : exchange_rate_db_(other.exchange_rate_db_) {
  (void) other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  (void) other;
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::LoadExchangeRate(const std::string &filename) {
  if (!exchange_rate_db_.Load(filename)) {
    return false;
  }
  return true;
}

Result<std::pair<std::string, double>,
       std::string> BitcoinExchange::ParseSimulationInput(const std::string &line,
                                                          const std::string &key_value_delimiter) {
  std::pair<std::string, std::string> key_value = SplitKeyValue(line, key_value_delimiter);

  std::string date = key_value.first;
  std::string value = key_value.second;

  if (date.empty() || value.empty()) {
    return Err("Error: bad input => " + line);
  }

  if (!IsValidDateFormat(date)) {
    return Err("Error: bad date format: " + date);
  }

  Result<double, std::string> to_double = StringToDouble(value);
  if (to_double.IsErr()) {
    return Err("Error: not a double representation");
  }
  if (to_double.IsOk() && (to_double.Unwrap() < 0)) {
    return Err("Error: not a positive number");
  }
  if (to_double.IsOk()
      && static_cast<long int>(to_double.Unwrap()) > 1000) {
    return Err("Error: too large a number");
  }

  return Ok(std::make_pair(date, to_double.Unwrap()));
}

void BitcoinExchange::SimulateExchange(const std::string &input_filename) {
  std::ifstream input_file(input_filename.c_str());
  if (!input_file.is_open()) {
    std::cerr << "Failed to open input_db file: " << input_filename << std::endl;
    return;
  }

  std::string line;
  // discard header
  std::getline(input_file, line);
  if (line != "date | value") {
    EvaluateLine(line);
  }
  // read the key-value pairs
  while (std::getline(input_file, line)) {
    EvaluateLine(line);
  }
}

void BitcoinExchange::EvaluateLine(std::string line) {
  const std::string kKeyValueDelimiter = " | ";

    Result<std::pair<std::string, double>, std::string>
        key_value = ParseSimulationInput(line, kKeyValueDelimiter);
    if (key_value.IsErr()) {
      std::cerr << key_value.UnwrapErr() << std::endl;
      return;
    }

    std::string date = key_value.Unwrap().first;
    double value = key_value.Unwrap().second;

    std::string exchange_rate_str = exchange_rate_db_.Find(date);
    Result<double, std::string> exchange_rate = StringToDouble(exchange_rate_str);
    if (exchange_rate.IsErr()) {
      std::cerr << "Error: exchange rate database is corrupted" << std::endl;
      return;
    }

    std::cout << date << " => " << value << " = " << value * exchange_rate.Unwrap() << std::endl;
}

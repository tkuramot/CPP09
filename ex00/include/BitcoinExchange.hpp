//
// Created by k.t. on 2023/12/17.
//

#ifndef CPP09_EX00_BITCOINEXCHANGE_HPP_
#define CPP09_EX00_BITCOINEXCHANGE_HPP_

#include <map>
#include <string>

class BitcoinExchange {
public:
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  ~BitcoinExchange();
  BitcoinExchange &operator=(const BitcoinExchange &other);

  BitcoinExchange(std::string file_name);
  void ProcessInput(std::string &file_name);

private:
  std::map<std::string, double> rates_;
  std::map<std::string, std::string> input_db_;
  void
  ReadBitcoinPriceDatabase(std::string &file_name) throw(std::runtime_error);
  void ReadInputDatabase(std::string &file_name);
  bool IsValidDate(const std::string &date);
  bool IsValidValue(const std::string &value);
};

#endif // CPP09_EX00_BITCOINEXCHANGE_HPP_

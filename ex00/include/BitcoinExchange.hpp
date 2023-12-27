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

  void ReadExchangeRateDatabase() throw(std::runtime_error);

private:
  std::map<std::string, double> rates_;
  static const std::string kDatabaseFile;
};

#endif // CPP09_EX00_BITCOINEXCHANGE_HPP_

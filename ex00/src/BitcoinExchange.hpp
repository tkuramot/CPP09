//
// Created by tkuramot on 4/3/24.
//

#ifndef BTC_SRC_BITCOINEXCHANGE_HPP_
#define BTC_SRC_BITCOINEXCHANGE_HPP_

#include "Database.hpp"

class BitcoinExchange {
 public:
  // canonical form
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  BitcoinExchange &operator=(const BitcoinExchange &other);
  ~BitcoinExchange();

  bool LoadExchangeRate(const std::string &filename);
  void SimulateExchange(const std::string &input_filename);

 private:
  Database exchange_rate_;
};

#endif //BTC_SRC_BITCOINEXCHANGE_HPP_

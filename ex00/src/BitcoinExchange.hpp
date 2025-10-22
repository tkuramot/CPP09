//
// Created by tkuramot on 4/3/24.
//

#ifndef BTC_SRC_BITCOINEXCHANGE_HPP_
#define BTC_SRC_BITCOINEXCHANGE_HPP_

#include "Database.hpp"
#include "Result.hpp"

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
  Database exchange_rate_db_;

  static Result<std::pair<std::string, double>, std::string> ParseSimulationInput(
      const std::string &line, const std::string &key_value_delimiter);
  void EvaluateLine(std::string line);
};

#endif //BTC_SRC_BITCOINEXCHANGE_HPP_

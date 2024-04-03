//
// Created by k.t. on 2024/02/12.
//

#include "BitcoinExchange.hpp"

int main() {
  BitcoinExchange exchange;
  exchange.LoadExchangeRate("../data.csv");
  exchange.SimulateExchange("../input.txt");
  return 0;
}
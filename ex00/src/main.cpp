//
// Created by k.t. on 2024/02/12.
//

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input.txt>" << std::endl;
    return 1;
  }

  BitcoinExchange exchange;
  exchange.LoadExchangeRate("data.csv");
  exchange.SimulateExchange(argv[1]);
  return 0;
}
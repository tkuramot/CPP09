//
// Created by k.t. on 2023/12/17.
//

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    std::exit(1);
  }

  try {
    BitcoinExchange btc("data.csv");
    std::string input_database = argv[1];
    btc.ProcessInput(input_database);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
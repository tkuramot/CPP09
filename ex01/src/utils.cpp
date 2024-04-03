//
// Created by tkuramot on 4/3/24.
//

#include "utils.hpp"
#include <sstream>

Result<int, std::string> StringToInt(const std::string &number) {
  std::istringstream ss(number);
  int result;
  ss >> result;
  if (ss.fail()) {
    return Err("Invalid number");
  }
  return Ok(result);
}

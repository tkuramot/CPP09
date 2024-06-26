//
// Created by tkuramot on 4/3/24.
//

#ifndef BTC_SRC_UTILS_HPP_
#define BTC_SRC_UTILS_HPP_

#include "Result.hpp"
#include <string>

Result<double, std::string> StringToDouble(const std::string &number);
Result<int, std::string> StringToInt(const std::string &number);

bool IsValidDateFormat(const std::string &date);

std::pair<std::string, std::string> SplitKeyValue(const std::string &line,
                                                  const std::string &key_value_delimiter);

#endif //BTC_SRC_UTILS_HPP_

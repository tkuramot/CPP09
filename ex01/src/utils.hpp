//
// Created by tkuramot on 4/3/24.
//

#ifndef BTC_SRC_UTILS_HPP_
#define BTC_SRC_UTILS_HPP_

#include "Result.hpp"
#include <string>

Result<int, std::string> StringToInt(const std::string &number);

#endif //BTC_SRC_UTILS_HPP_

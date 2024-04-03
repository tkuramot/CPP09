//
// Created by tkuramot on 4/3/24.
//

#include "utils.hpp"
#include <sstream>

Result<double, std::string> StringToDouble(const std::string &number) {
  std::istringstream ss(number);
  double result;
  ss >> result;
  if (ss.fail()) {
    return Err("Invalid number");
  }
  return Ok(result);
}

Result<int, std::string> StringToInt(const std::string &number) {
  std::istringstream ss(number);
  int result;
  ss >> result;
  if (ss.fail()) {
    return Err("Invalid number");
  }
  return Ok(result);
}

bool IsValidDateFormat(const std::string &date) {
  const std::string format = "YYYY-MM-DD";
  if (date.size() != format.size()) {
    return false;
  }

  if (date[4] != '-' || date[7] != '-') {
    return false;
  }

  Result<int, std::string> month = StringToInt(date.substr(5, 2));
  if (month.IsErr()) {
    return false;
  }
  if (month.Unwrap() < 1 || month.Unwrap() > 12) {
    return false;
  }

  Result<int, std::string> day = StringToInt(date.substr(8, 2));
  if (day.IsErr()) {
    return false;
  }
  if (day.Unwrap() < 1 || day.Unwrap() > 31) {
    return false;
  }
  return true;
}

std::pair<std::string, std::string> SplitKeyValue(const std::string &line,
                                                            const std::string &key_value_delimiter) {
  size_t delimiter_pos = line.find(key_value_delimiter);
  if (delimiter_pos == std::string::npos) {
    return std::make_pair(line, "");
  }
  return std::make_pair(
      line.substr(0, delimiter_pos),
      line.substr(delimiter_pos + key_value_delimiter.length())
  );
}

//
// Created by tkuramot on 4/3/24.
//

#include "RPN.hpp"
#include "utils.hpp"
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN &other) {
  (void) other;
}

RPN &RPN::operator=(const RPN &other) {
  if (this == &other) {
    return *this;
  }
  return *this;
}

RPN::~RPN() {}

Result<int, std::string> RPN::Calculate(const std::string &rpn_string) {
  const std::string kAvailableOperators = "+-/*";
  std::stack<int> stack;

  std::stringstream ss(rpn_string);
  std::string token;
  while (std::getline(ss, token, ' ')) {
    Result<int, std::string> to_int = StringToInt(token);
    if (to_int.IsOk()) {
      stack.push(to_int.Unwrap());
      continue;
    }

    bool has_enough_operands = (stack.size() >= 2);
    bool is_valid_operator = (token.size() == 1
        && kAvailableOperators.find(token[0]) != std::string::npos);
    if (!has_enough_operands || !is_valid_operator) {
      return Err("Error");
    }

    int right_opd = stack.top();
    stack.pop();
    int left_opd = stack.top();
    stack.pop();
    char opr = token[0];
    if (opr == '+') {
      stack.push(left_opd + right_opd);
    }
    if (opr == '-') {
      stack.push(left_opd - right_opd);
    }
    if (opr == '*') {
      stack.push(left_opd * right_opd);
    }
    if (opr == '/') {
      if (right_opd == 0) {
        return Err("Error");
      }
      stack.push(left_opd / right_opd);
    }
  }

  // stack must have only one element, which is the answer
  if (stack.size() != 1) {
    return Err("Error");
  }
  return Ok(stack.top());
}

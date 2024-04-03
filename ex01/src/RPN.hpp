//
// Created by tkuramot on 4/3/24.
//

#ifndef EX01__RPN_HPP_
#define EX01__RPN_HPP_

#include <stack>
#include <string>
#include "Result.hpp"

class RPN {
 public:
  static Result<int, std::string> Calculate(const std::string &rpn_string);

 private:
  // canonical form
  RPN();
  RPN(const RPN &other);
  RPN &operator=(const RPN &other);
  ~RPN();
};

#endif //EX01__RPN_HPP_

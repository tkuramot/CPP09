#include <iostream>
#include "Result.hpp"
#include "RPN.hpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << "<reverse polish notation string>" << std::endl;
    return 1;
  }

  Result<int, std::string> rpn_result = RPN::Calculate(argv[1]);
  if (rpn_result.IsErr()) {
    std::cerr << rpn_result.UnwrapErr() << std::endl;
    return 1;
  }
  std::cout << rpn_result.Unwrap() << std::endl;
  return 0;
}

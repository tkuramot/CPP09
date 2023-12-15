//
// Created by k.t. on 2023/12/10.
//

#include "Span.hpp"
#include <iostream>

int main() {
  {
    Span span(5);
    span.AddNumber(5);
    span.AddNumber(3);
    span.AddNumber(17);
    span.AddNumber(9);
    span.AddNumber(11);
    std::cout << span.ShortestSpan() << std::endl;
    std::cout << span.LongestSpan() << std::endl;
  }
  {
    std::vector<int> v(10, 10);
    Span span(10);
    span.AddNumberRange(v.begin(), v.end());
    std::cout << span.ShortestSpan() << std::endl;
    std::cout << span.LongestSpan() << std::endl;
  }
  return 0;
}
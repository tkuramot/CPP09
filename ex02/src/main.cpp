#include "GroupIterator.hpp"
#include "PMergeMe.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v1;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
  }
  GroupIterator<std::vector<int>::iterator> start(v1.begin(), 2);
  GroupIterator<std::vector<int>::iterator> end(v1.end(), 2);
  for (; start != end; ++start) {
    int x = *start;
    std::cout << x << std::endl;
  }
  std::cout << "Sorting" << std::endl;
  PMergeMe<std::vector<int> >::Sort(v1);
  for (int i = 0; i < 10; ++i) {
    std::cout << v1[i] << std::endl;
  }
}

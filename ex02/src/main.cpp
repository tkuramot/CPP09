#include "PMergeMe.hpp"
#include <vector>

int main() {
  // Jacobsthal<int> j(10);
  // for (int i = 0; i < 10; ++i) {
  //   printf("Jacobsthal(%d) = %d\n", i, j[i]);
  // }
  std::vector<int> v;
  for (int i = 0; i < 99; ++i) {
    v.push_back(i);
  }
  PMergeMe::Sort<int>(v);
  return 0;
}

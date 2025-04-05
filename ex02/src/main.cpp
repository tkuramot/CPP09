#include "PMergeMe.hpp"
#include <vector>

int main() {
  // Jacobsthal<int> j(10);
  // for (int i = 0; i < 10; ++i) {
  //   printf("Jacobsthal(%d) = %d\n", i, j[i]);
  // }
  std::vector<int> v;
  v.push_back(9);
  v.push_back(2);
  v.push_back(21);
  v.push_back(15);
  v.push_back(20);
  v.push_back(3);
  v.push_back(7);
  v.push_back(1);
  v.push_back(6);
  v.push_back(11);
  v.push_back(17);
  v.push_back(4);
  v.push_back(19);
  v.push_back(16);
  v.push_back(10);
  v.push_back(13);
  v.push_back(18);
  v.push_back(5);
  v.push_back(12);
  v.push_back(22);
  v.push_back(8);
  v.push_back(14);
  PMergeMe::Sort<int>(v);
  return 0;
}

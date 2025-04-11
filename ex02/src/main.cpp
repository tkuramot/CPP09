#include "PMergeMe.hpp"
#include <vector>

int main() {
  std::vector<int> v;
  for (int i = 20; i > 0; --i) {
    v.push_back(i);
  }
  // for (int i = 0; i < 20; ++i) {
  //   v.push_back(i);
  // }
  // v.push_back(9);
  // v.push_back(2);
  // v.push_back(21);
  // v.push_back(15);
  // v.push_back(20);
  // v.push_back(3);
  // v.push_back(7);
  // v.push_back(1);
  // v.push_back(6);
  // v.push_back(11);
  // v.push_back(17);
  // v.push_back(4);
  // v.push_back(19);
  // v.push_back(16);
  // v.push_back(10);
  // v.push_back(13);
  // v.push_back(18);
  // v.push_back(5);
  // v.push_back(12);
  // v.push_back(22);
  // v.push_back(8);
  // v.push_back(14);
  PMergeMe::Sort<int>(v);
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  return 0;
}

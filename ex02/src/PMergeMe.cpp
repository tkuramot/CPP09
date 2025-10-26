#include "PMergeMe.hpp"

PMergeMe::PMergeMe() {}
PMergeMe::PMergeMe(const PMergeMe &other) { (void)other; }
PMergeMe &PMergeMe::operator=(const PMergeMe &other) {
  if (this == &other) { return *this; }
  return *this;
}
PMergeMe::~PMergeMe() {}

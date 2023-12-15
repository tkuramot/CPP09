#include "easyfind.hpp"

template <typename T>
typename T::const_iterator Easyfind(T &container, int target) {
  typename T::const_iterator itr = container.begin();
  while (itr != container.end()) {
    if (*itr == target) {
      return itr;
    }
    itr++;
  }
  return itr;
}

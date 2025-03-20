#include "Jacobsthal.hpp"

int main() {
  Jacobsthal<int> j(10);
  for (int i = 0; i < 10; ++i) {
    printf("Jacobsthal(%d) = %d\n", i, j[i]);
  }
  return 0;
}

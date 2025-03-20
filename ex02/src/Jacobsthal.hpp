#ifndef JACOBSTHAL_HPP
#define JACOBSTHAL_HPP

#include <vector>

template <typename T> class Jacobsthal {
public:
  Jacobsthal(int n) {
    seq_.resize(n);
    Fill(&seq_);
  }
  ~Jacobsthal() {}

private:
  std::vector<T> seq_;

  Jacobsthal() {}
  Jacobsthal(const Jacobsthal &) {}
  Jacobsthal &operator=(const Jacobsthal &) {}
  void Fill(const std::vector<T> &seq) {
    if (seq.size() > 0) {
      seq[0] = 0;
    }
    if (seq.size() > 1) {
      seq[1] = 1;
    }

    if (seq.size() <= 2) {
      return;
    }
    for (size_t i = 2; i < seq.size(); ++i) {
      seq[i] = seq[i - 1] + 2 * seq[i - 2];
    }
  }
};

#endif // JACOBSTHAL_HPP

#ifndef JACOBSTHAL_HPP
#define JACOBSTHAL_HPP

#include <vector>

template <typename T> class Jacobsthal {
public:
  Jacobsthal(int n) { Fill(n); }
  ~Jacobsthal() {}
  const T &operator[](int i) const { return seq_[i]; }
  T &operator[](int i) { return seq_[i]; }

private:
  std::vector<T> seq_;

  Jacobsthal() {}
  Jacobsthal(const Jacobsthal &) {}
  Jacobsthal &operator=(const Jacobsthal &) {}
  void Fill(int n) {
    seq_.resize(n);
    if (seq_.size() > 0) {
      seq_[0] = 0;
    }
    if (seq_.size() > 1) {
      seq_[1] = 1;
    }

    if (seq_.size() <= 2) {
      return;
    }
    for (size_t i = 2; i < seq_.size(); ++i) {
      seq_[i] = seq_[i - 1] + 2 * seq_[i - 2];
    }
  }
};

#endif // JACOBSTHAL_HPP

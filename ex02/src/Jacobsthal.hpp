#ifndef JACOBSTHAL_HPP
#define JACOBSTHAL_HPP

#include <vector>

template <typename T> class Jacobsthal {
public:
  Jacobsthal(int n) { seq_ = Generate(n); }
  ~Jacobsthal() {}
  const T &operator[](int i) const { return seq_[i]; }
  T &operator[](int i) { return seq_[i]; }

private:
  std::vector<T> seq_;

  Jacobsthal() {}
  Jacobsthal(const Jacobsthal &) {}
  Jacobsthal &operator=(const Jacobsthal &) {}
  std::vector<T> Generate(int n) {
    std::vector<T> seq(n);
    if (seq.size() > 0) {
      seq[0] = 0;
    }
    if (seq.size() > 1) {
      seq[1] = 1;
    }

    if (seq.size() <= 2) {
      return seq;
    }
    for (size_t i = 2; i < seq.size(); ++i) {
      seq[i] = seq[i - 1] + 2 * seq[i - 2];
    }
    return seq;
  }
};

#endif // JACOBSTHAL_HPP

#pragma once

template <typename T, typename E> class Result;

namespace result {
template <typename E> class Error {
public:
  explicit Error(E error) : error_(error) {}

  Error(const Error &other) : error_(other.error_) {}

  Error &operator=(const Error &other) {
    if (this == &other) {
      return *this;
    }
    error_ = other.error_;
  }

  ~Error() {}

  template <typename V, typename F> operator Result<V, F>() const {
    return Result<V, F>(V(), error_, /* has_value= */ false);
  }

private:
  E error_;
};
} // namespace result
#pragma once

template <typename T, typename E> class Result;

namespace result {
template <typename T> class Value {
public:
  explicit Value(T value) : value_(value) {}

  Value(const Value &other) : value_(other.value_) {}

  Value &operator=(const Value &other) {
    if (this == &other) {
      return *this;
    }
    value_ = other.value_;
  }

  ~Value() {}

  template <typename V, typename E> operator Result<V, E>() const {
    return Result<V, E>(value_, E(), /* has_value= */ true);
  }

private:
  T value_;
};
} // namespace result
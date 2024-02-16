#pragma once

#include "Error.hpp"
#include "Value.hpp"
#include <stdexcept>

template <typename T, typename E> class Result {
public:
  Result(T value, E error, bool has_value)
      : value_(value), error_(error), has_value_(has_value) {}

  Result(const Result &other)
      : value_(other.value_), error_(other.error_),
        has_value_(other.has_value_) {}

  Result &operator=(const Result &other) {
    if (this == &other) {
      return *this;
    }
    value_ = other.value_;
    error_ = other.error_;
    has_value_ = other.has_value_;
  }

  ~Result() {}

  T Unwrap() const {
    if (!IsOk()) {
      throw std::runtime_error("Result does not have a value");
    }
    return value_;
  }

  E UnwrapErr() const {
    if (!IsErr()) {
      throw std::runtime_error("Result does not have an error");
    }
    return error_;
  }

  bool IsOk() const { return has_value_; }

  bool IsErr() const { return !has_value_; }

private:
  T value_;
  E error_;
  bool has_value_;
};

template <typename T> result::Value<T> Ok(T value) {
  return result::Value<T>(value);
}

template <typename E> result::Error<E> Err(E error) {
  return result::Error<E>(error);
}

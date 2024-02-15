//
// Created by k.t. on 2024/02/16.
//

#ifndef BTC_EX00_SRC_ERRORVALUE_HPP_
#define BTC_EX00_SRC_ERRORVALUE_HPP_

#include "Result.hpp"

template <typename T> class ErrorValue {
public:
  explicit ErrorValue(T ok);
  ErrorValue(const ErrorValue &other);
  ~ErrorValue();

  template <typename V, typename E> operator Result<V, E>() const;

private:
  T t;
};

template <typename T> ErrorValue<T>::ErrorValue(T ok) : t(ok) {}

template <typename T>
ErrorValue<T>::ErrorValue(const ErrorValue &other) : t(other.t) {}

template <typename T> ErrorValue<T>::~ErrorValue() {}

template <typename T>
template <typename V, typename E>
ErrorValue<T>::operator Result<V, E>() const {
  return Result<V, E>(t);
}

template <typename T> ErrorValue<T> Error(T t) { return ErrorValue<T>(t); }

#endif // BTC_EX00_SRC_ERRORVALUE_HPP_

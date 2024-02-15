//
// Created by k.t. on 2024/02/16.
//

#ifndef BTC_EX00_SRC_OK_HPP_
#define BTC_EX00_SRC_OK_HPP_

#include "Result.hpp"

template <typename T> class OkValue {
public:
  explicit OkValue(T ok);
  OkValue(const OkValue &other);
  ~OkValue();

  template <typename V, typename E> operator Result<V, E>() const;

private:
  T t;
};

template <typename T> OkValue<T>::OkValue(T ok) : t(ok) {}

template <typename T> OkValue<T>::OkValue(const OkValue &other) : t(other.t) {}

template <typename T> OkValue<T>::~OkValue() {}

template <typename T>
template <typename V, typename E>
OkValue<T>::operator Result<V, E>() const {
  return Result<V, E>(t);
}

template <typename T> OkValue<T> Ok(T t) { return OkValue<T>(t); }

#endif // BTC_EX00_SRC_OK_HPP_

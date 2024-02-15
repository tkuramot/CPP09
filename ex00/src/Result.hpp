//
// Created by k.t. on 2024/02/16.
//

#ifndef BTC_EX00_SRC_RESULT_HPP_
#define BTC_EX00_SRC_RESULT_HPP_

#include <cassert>

template <typename T, typename E> class Result {
public:
  explicit Result(T ok);
  explicit Result(E err);
  Result(const Result &other);
  ~Result();

  bool IsOk() const;
  bool IsError() const;
  const T &Ok() const;
  const E &Error() const;

private:
  enum Tag {
    kOk,
    kError,
  };
  Tag tag_;
  T ok_;
  E err_;
};

template <typename T, typename E>
Result<T, E>::Result(T ok) : tag_(kOk), ok_(ok) {}

template <typename T, typename E>
Result<T, E>::Result(E err) : tag_(kError), err_(err) {}

template <typename T, typename E>
Result<T, E>::Result(const Result &other) : tag_(other.tag_) {
  if (tag_ == kOk) {
    ok_ = other.ok_;
    return;
  }
  if (tag_ == kError) {
    err_ = other.err_;
    return;
  }
}

template <typename T, typename E> Result<T, E>::~Result() {
  if (tag_ == kOk) {
    ok_.~T();
    return;
  }
  if (tag_ == kError) {
    err_.~E();
    return;
  }
}

template <typename T, typename E> bool Result<T, E>::IsOk() const {
  return tag_ == kOk;
}

template <typename T, typename E> bool Result<T, E>::IsError() const {
  return tag_ == kError;
}

template <typename T, typename E> const T &Result<T, E>::Ok() const {
  assert(tag_ == kOk);
  return ok_;
}

template <typename T, typename E> const E &Result<T, E>::Error() const {
  assert(tag_ == kError);
  return err_;
}

#endif // BTC_EX00_SRC_RESULT_HPP_

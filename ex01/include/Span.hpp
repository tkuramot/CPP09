//
// Created by k.t. on 2023/12/12.
//

#ifndef A_OUT_INCLUDE_SPAN_HPP_
#define A_OUT_INCLUDE_SPAN_HPP_

#include <list>

class Span {
public:
  class TooManyElements : public std::exception {
  public:
    const char *what() const throw();
  };
  class TooFewElements : public std::exception {
  public:
    const char *what() const throw();
  };
  Span(unsigned int n);
  Span(const Span &obj);
  ~Span();
  Span &operator=(const Span &obj);

  void AddNumber(int n) throw(TooManyElements);
  template <typename T>
  void AddNumberRange(T begin, T end) throw(Span::TooManyElements);
  int ShortestSpan() throw(TooFewElements);
  int LongestSpan() throw(TooFewElements);

private:
  unsigned int n_;
  std::list<int> list_;
};

template <typename T>
void Span::AddNumberRange(T begin, T end) throw(Span::TooManyElements) {
  if (list_.size() >= n_) {
    throw Span::TooManyElements();
  }
  if (list_.size() + static_cast<size_t>(std::distance(begin, end)) > n_) {
    throw Span::TooManyElements();
  }
  for (T itr = begin; itr != end; ++itr) {
    list_.push_back(*itr);
  }
}

#endif // A_OUT_INCLUDE_SPAN_HPP_

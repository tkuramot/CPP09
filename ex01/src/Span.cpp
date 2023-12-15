//
// Created by k.t. on 2023/12/12.
//

#include "Span.hpp"

const char *Span::TooManyElements::what() const throw() {
  return "Too many elements";
}

const char *Span::TooFewElements::what() const throw() {
  return "Too few elements";
}

Span::Span(unsigned int n) : n_(n) {}

Span::Span(const Span &obj) : n_(obj.n_) {}

Span::~Span() {}

Span &Span::operator=(const Span &obj) {
  (void)obj;
  return *this;
}

void Span::AddNumber(int n) throw(Span::TooManyElements) {
  if (list_.size() >= n_) {
    throw Span::TooManyElements();
  }
  list_.push_back(n);
}

int Span::ShortestSpan() throw(Span::TooFewElements) {
  if (list_.size() <= 1) {
    throw Span::TooFewElements();
  }
  std::list<int> temp(list_);
  int shortest_span = std::numeric_limits<int>::max();
  for (std::list<int>::iterator itr = temp.begin(); itr != --temp.end();
       ++itr) {
    shortest_span = std::min(shortest_span, std::abs(*++itr - *--itr));
  }
  return shortest_span;
}

int Span::LongestSpan() throw(Span::TooFewElements) {
  if (list_.size() <= 1) {
    throw Span::TooFewElements();
  }
  std::list<int> temp(list_);
  int longest_span = std::numeric_limits<int>::min();
  for (std::list<int>::iterator itr = temp.begin(); itr != --temp.end();
       ++itr) {
    longest_span = std::max(longest_span, std::abs(*++itr - *--itr));
  }
  return longest_span;
}
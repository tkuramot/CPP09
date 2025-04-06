#ifndef GROUP_ITERATOR_HPP
#define GROUP_ITERATOR_HPP

#include <iostream>
#include <iterator>

template <typename Iterator> class GroupIterator {
public:
  typedef
      typename std::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  typedef typename std::iterator_traits<Iterator>::pointer pointer;
  typedef typename std::iterator_traits<Iterator>::reference reference;

  // Constructors
  GroupIterator(Iterator it, difference_type size) : it_(it), size_(size) {}
  template <typename T>
  GroupIterator(GroupIterator<T> it, difference_type size)
      : it_(it.Base()), size_(it.Size() * size) {}

  // Element access
  reference operator*() const { return *std::next(it_, size_ - 1); }
  pointer operator->() const { return &(operator*()); }

  // Increment and decrement operators
  GroupIterator &operator++() {
    std::advance(it_, size_);
    return *this;
  }
  GroupIterator operator++(int) {
    GroupIterator tmp(*this);
    operator++();
    return tmp;
  }
  GroupIterator &operator--() {
    std::advance(it_, -size_);
    return *this;
  }
  GroupIterator operator--(int) {
    GroupIterator tmp(*this);
    operator--();
    return tmp;
  }
  GroupIterator &operator+=(difference_type n) {
    std::advance(it_, n * size_);
    return *this;
  }
  GroupIterator &operator-=(difference_type n) {
    std::advance(it_, -n * size_);
    return *this;
  }

  // Arithmetic operators
  GroupIterator operator+(difference_type n) const {
    return GroupIterator(it_ + n * size_, size_);
  }
  GroupIterator operator-(difference_type n) const {
    return GroupIterator(it_ - n * size_, size_);
  }
  difference_type operator-(const GroupIterator &rhs) const {
    return std::distance(rhs.it_, it_) / size_;
  }

  // Logical operators
  bool operator==(const GroupIterator &rhs) const { return it_ == rhs.it_; }
  bool operator!=(const GroupIterator &rhs) const { return it_ != rhs.it_; }
  bool operator<(const GroupIterator &rhs) const { return it_ < rhs.it_; }
  bool operator>(const GroupIterator &rhs) const { return it_ > rhs.it_; }

  // Accessors
  Iterator Base() const { return it_; }
  difference_type Size() const { return size_; }
  static void Swap(GroupIterator lhs, GroupIterator rhs) {
    for (difference_type i = 0; i < lhs.size_; ++i) {
      std::iter_swap(lhs.it_ + i, rhs.it_ + i);
    }
  }

  // For debugging only
  static void DebugPrint(GroupIterator<Iterator> begin,
                         GroupIterator<Iterator> end) {
    for (GroupIterator<Iterator> it = begin; it != end; ++it) {
      std::cerr << *it << " ";
    }
    std::cerr << std::endl;
  }

private:
  Iterator it_;
  difference_type size_;

  GroupIterator() {}
};

#endif // GROUP_ITERATOR_HPP

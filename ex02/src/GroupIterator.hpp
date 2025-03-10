#ifndef GROUP_ITERATOR_HPP
#define GROUP_ITERATOR_HPP

#include <algorithm>
#include <iterator>

template <typename Iterator> class GroupIterator {
public:
  typedef typename std::iterator_traits<Iterator>::iterator_category
      iterator_category;
  typedef Iterator iterator_type;
  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  typedef
      typename std::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename std::iterator_traits<Iterator>::pointer pointer;
  typedef typename std::iterator_traits<Iterator>::reference reference;

  GroupIterator() {}
  GroupIterator(Iterator it, difference_type size) : it_(it), size_(size) {}

  Iterator BastIt() const { return it_; }
  difference_type Size() const { return size_; }

  // Element access
  reference operator*() const { return *it_; }
  pointer operator->() const { return it_.operator->(); }

  // Increment and decrement
  GroupIterator &operator++() {
    std::advance(it_, size_);
    return *this;
  }

  GroupIterator operator--() {
    GroupIterator tmp = *this;
    std::advance(it_, -size_);
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

  // Comparison operators
  bool operator==(const GroupIterator &other) const {
    return BastIt() == other.BastIt();
  }

  bool operator!=(const GroupIterator &other) const {
    return BastIt() != other.BastIt();
  }

private:
  Iterator it_;
  difference_type size_;
};

// Relational operators
template <typename Iterator>
bool operator<(const GroupIterator<Iterator> &it1,
               const GroupIterator<Iterator> &it2) {
  return it1.BastIt() < it2.BastIt();
}

template <typename Iterator>
bool operator>(const GroupIterator<Iterator> &it1,
               const GroupIterator<Iterator> &it2) {
  return it1.BastIt() > it2.BastIt();
}

template <typename Iterator>
bool operator<=(const GroupIterator<Iterator> &it1,
                const GroupIterator<Iterator> &it2) {
  return it1.BastIt() <= it2.BastIt();
}

template <typename Iterator>
bool operator>=(const GroupIterator<Iterator> &it1,
                const GroupIterator<Iterator> &it2) {
  return it1.BastIt() >= it2.BastIt();
}

// Arithmetic operators
template <typename Iterator>
GroupIterator<Iterator>
operator+(GroupIterator<Iterator> it,
          typename GroupIterator<Iterator>::difference_type n) {
  return GroupIterator<Iterator>(it.BastIt() + n * it.Size(), it.Size());
}

template <typename Iterator>
GroupIterator<Iterator>
operator+(typename GroupIterator<Iterator>::difference_type n,
          GroupIterator<Iterator> it) {
  return GroupIterator<Iterator>(it.BastIt() + n * it.Size(), it.Size());
}

template <typename Iterator>
GroupIterator<Iterator>
operator-(GroupIterator<Iterator> it,
          typename GroupIterator<Iterator>::difference_type n) {
  return GroupIterator<Iterator>(it.BastIt() - n * it.Size(), it.Size());
}

template <typename Iterator>
typename GroupIterator<Iterator>::difference_type
operator-(GroupIterator<Iterator> it1, GroupIterator<Iterator> it2) {
  return (it1.BastIt() - it2.BastIt()) / it1.Size();
}

// Swap
// TODO swap ranges. care for overlapping ranges.
template <typename Iterator>
void Swap(GroupIterator<Iterator> &it1, GroupIterator<Iterator> &it2) {
  std::iter_swap(it1.BastIt(), it2.BastIt());
}

// Construction functions
template <typename Iterator>
GroupIterator<Iterator>
MakeGroupIterator(Iterator it,
                  typename GroupIterator<Iterator>::difference_type size) {
  return GroupIterator<Iterator>(it, size);
}

template <typename Iterator>
GroupIterator<Iterator>
MakeGroupIterator(GroupIterator<Iterator> it,
                  typename GroupIterator<Iterator>::difference_type size) {
  return GroupIterator<Iterator>(it.BastIt(), size);
}

#endif // GROUP_ITERATOR_HPP

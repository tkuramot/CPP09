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

  // Comparison operators
  bool operator==(const GroupIterator &other) const {
    return BastIt() == other.BastIt();
  }
  bool operator!=(const GroupIterator &other) const {
    return BastIt() != other.BastIt();
  }

  // Arithmetic operators
  GroupIterator &operator+=(difference_type n) {
    std::advance(it_, n * size_);
    return *this;
  }
  GroupIterator &operator-=(difference_type n) {
    std::advance(it_, -n * size_);
    return *this;
  }

private:
  Iterator it_;
  difference_type size_;
};

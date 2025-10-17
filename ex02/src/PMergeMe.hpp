#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <list>
#include <algorithm>

class PMergeMe
{
public:
  static void sort(std::vector<int>::iterator first,
                   std::vector<int>::iterator last);

  static void sort(std::deque<int>::iterator first,
                   std::deque<int>::iterator last);

private:
  template <typename Iterator>
  class GroupIterator
  {
  public:
    typedef Iterator iterator_type;
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    typedef typename std::iterator_traits<Iterator>::pointer pointer;
    typedef typename std::iterator_traits<Iterator>::reference reference;

    GroupIterator() : it_(), size_(0) {}
    GroupIterator(Iterator it, difference_type size) : it_(it), size_(size) {}

    iterator_type base() const { return it_; }
    difference_type size() const { return size_; }

    reference operator*() const
    {
      Iterator tmp = it_;
      std::advance(tmp, size_ - 1);
      return *tmp;
    }

    pointer operator->() const
    {
      return &(operator*());
    }

    GroupIterator &operator++()
    {
      std::advance(it_, size_);
      return *this;
    }

    GroupIterator &operator--()
    {
      std::advance(it_, -size_);
      return *this;
    }

    GroupIterator &operator+=(difference_type n)
    {
      it_ += size_ * n;
      return *this;
    }

    GroupIterator &operator-=(difference_type n)
    {
      it_ -= size_ * n;
      return *this;
    }

    bool operator==(const GroupIterator &rhs) const
    {
      return it_ == rhs.it_;
    }

    bool operator!=(const GroupIterator &rhs) const
    {
      return it_ != rhs.it_;
    }

    bool operator<(const GroupIterator &rhs) const
    {
      return it_ < rhs.it_;
    }

    bool operator<=(const GroupIterator &rhs) const
    {
      return it_ <= rhs.it_;
    }

    bool operator>(const GroupIterator &rhs) const
    {
      return it_ > rhs.it_;
    }

    bool operator>=(const GroupIterator &rhs) const
    {
      return it_ >= rhs.it_;
    }

    GroupIterator operator+(difference_type n) const
    {
      GroupIterator tmp = *this;
      tmp += n;
      return tmp;
    }

    GroupIterator operator-(difference_type n) const
    {
      GroupIterator tmp = *this;
      tmp -= n;
      return tmp;
    }

    difference_type operator-(const GroupIterator &rhs) const
    {
      return (it_ - rhs.it_) / size_;
    }

  private:
    Iterator it_;
    difference_type size_;
  };

  template <typename Iterator>
  static void iterSwap(GroupIterator<Iterator> lhs, GroupIterator<Iterator> rhs)
  {
    Iterator lhs_begin = lhs.base();
    Iterator lhs_end = lhs.base();
    std::advance(lhs_end, lhs.size());
    Iterator rhs_begin = rhs.base();

    std::swap_ranges(lhs_begin, lhs_end, rhs_begin);
  }

  template <typename Iterator>
  static void iterSwapIf(Iterator a, Iterator b)
  {
    if (*b < *a)
    {
      std::iter_swap(a, b);
    }
  }

  template <typename Iterator>
  static void iterSwapIf(GroupIterator<Iterator> a, GroupIterator<Iterator> b)
  {
    if (*b < *a)
    {
      iterSwap(a, b);
    }
  }

  template <typename ListIter, typename GroupIter>
  static ListIter binarySearchInsertionPoint(ListIter first, ListIter last, const GroupIter &value_iter)
  {
    ListIter it;
    typename std::iterator_traits<ListIter>::difference_type count, step;
    count = std::distance(first, last);

    while (count > 0)
    {
      it = first;
      step = count / 2;
      std::advance(it, step);

      // Compare dereferenced values
      if (!(*value_iter < **it))
      {
        first = ++it;
        count -= step + 1;
      }
      else
      {
        count = step;
      }
    }
    return first;
  }

  static void sortImpl(GroupIterator<std::vector<int>::iterator> first,
                       GroupIterator<std::vector<int>::iterator> last);

  static void sortImpl(GroupIterator<std::deque<int>::iterator> first,
                       GroupIterator<std::deque<int>::iterator> last);

  PMergeMe();
  PMergeMe(const PMergeMe &);
};

#endif

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <list>
#include <string>
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>

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
    typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
    typedef Iterator iterator_type;
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    typedef typename std::iterator_traits<Iterator>::pointer pointer;
    typedef typename std::iterator_traits<Iterator>::reference reference;

    GroupIterator() : _it(), _size(0) {}
    GroupIterator(Iterator it, difference_type size) : _it(it), _size(size) {}

    iterator_type base() const { return _it; }
    difference_type size() const { return _size; }

    reference operator*() const
    {
      Iterator tmp = _it;
      std::advance(tmp, _size - 1);
      return *tmp;
    }

    pointer operator->() const
    {
      return &(operator*());
    }

    GroupIterator &operator++()
    {
      std::advance(_it, _size);
      return *this;
    }

    GroupIterator operator++(int)
    {
      GroupIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    GroupIterator &operator--()
    {
      std::advance(_it, -_size);
      return *this;
    }

    GroupIterator operator--(int)
    {
      GroupIterator tmp = *this;
      --(*this);
      return tmp;
    }

    GroupIterator &operator+=(difference_type n)
    {
      _it += _size * n;
      return *this;
    }

    GroupIterator &operator-=(difference_type n)
    {
      _it -= _size * n;
      return *this;
    }

    bool operator==(const GroupIterator &rhs) const
    {
      return _it == rhs._it;
    }

    bool operator!=(const GroupIterator &rhs) const
    {
      return _it != rhs._it;
    }

    bool operator<(const GroupIterator &rhs) const
    {
      return _it < rhs._it;
    }

    bool operator<=(const GroupIterator &rhs) const
    {
      return _it <= rhs._it;
    }

    bool operator>(const GroupIterator &rhs) const
    {
      return _it > rhs._it;
    }

    bool operator>=(const GroupIterator &rhs) const
    {
      return _it >= rhs._it;
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
      return (_it - rhs._it) / _size;
    }

  private:
    Iterator _it;
    difference_type _size;
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
  static ListIter customUpperBound(ListIter first, ListIter last, const GroupIter &value_iter)
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

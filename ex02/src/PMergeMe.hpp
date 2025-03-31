#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include "GroupIterator.hpp"
#include <algorithm>
#include <deque>
#include <iostream>

class PMergeMe {
public:
  template <typename T> static void Sort(std::vector<T> &v) {
    SortImpl<std::vector<T> >(
        GroupIterator<typename std::vector<T>::iterator>(v.begin(), 1),
        GroupIterator<typename std::vector<T>::iterator>(v.end(), 1));
  }
  template <typename T> static void Sort(std::deque<T> &d) {
    SortImpl<std::deque<T> >(
        GroupIterator<typename std::deque<T>::iterator>(d.begin(), 1),
        GroupIterator<typename std::deque<T>::iterator>(d.end(), 1));
  }

private:
  template <typename Container>
  static void SortImpl(GroupIterator<typename Container::iterator> first,
                       GroupIterator<typename Container::iterator> last) {
    std::cout << first.Size() << std::endl;
    typename GroupIterator<typename Container::iterator>::difference_type size =
        last - first;
    if (size < 2) {
      return;
    }

    bool has_stray = (size % 2);
    GroupIterator<typename Container::iterator> end = has_stray ? last - 1 : last;

    // Sort in pairs
    for (GroupIterator<typename Container::iterator> it = first; it != end; it += 2) {
      std::cout << *it << std::endl;
      if (*it < *(it + 1)) {
        continue;
      }
      std::iter_swap(it, std::next(it.Base()));
    }

    // Recursively sort the pairs
    SortImpl<Container>(GroupIterator<typename Container::iterator>(first, 2),
                        GroupIterator<typename Container::iterator>(end, 2));

    // Separate the sorted pairs into chain and pend
    Container chain;
    chain.push_back(*first);
    chain.push_back(*(first + 1));
    Container pend;
    for (GroupIterator<typename Container::iterator> it = first; it != end; it += 2) {
      chain.push_back(*it);
      pend.push_back(*(it + 1));
    }
    if (has_stray) {
      pend.push_back(*last);
    }

    // insert using jacobsthal sequence
    //
    // overwrite c with chain
  }
};

#endif // PMERGE_ME_HPP

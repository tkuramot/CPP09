#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include "GroupIterator.hpp"

template <typename Container> class PMergeMe {
public:
  static void Sort(Container &c) {
    if (c.size() < 2)
      return;
    SortImpl(GroupIterator<typename Container::iterator>(c.begin(), 1),
             GroupIterator<typename Container::iterator>(c.end(), 1));
  }

private:
  template <typename Iterator>
  static void SortImpl(GroupIterator<Iterator> first, GroupIterator<Iterator> last) {
    (void)last;
    GroupIterator<Iterator> next = first + 1;
    Swap(first, next);
  }
};

#endif // PMERGE_ME_HPP

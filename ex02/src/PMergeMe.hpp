#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include "GroupIterator.hpp"
#include <algorithm>
#include <deque>
#include <iostream>

class PMergeMe {
public:
  template <typename T> static void Sort(std::vector<T> &v) {
    SortImpl<std::vector<GroupIterator<typename std::vector<T>::iterator> > >(
        GroupIterator<typename std::vector<T>::iterator>(v.begin(), 1),
        GroupIterator<typename std::vector<T>::iterator>(v.end(), 1));
  }
  template <typename T> static void Sort(std::deque<T> &d) {
    SortImpl<std::vector<GroupIterator<typename std::deque<T>::iterator> > >(
        GroupIterator<typename std::deque<T>::iterator>(d.begin(), 1),
        GroupIterator<typename std::deque<T>::iterator>(d.end(), 1));
  }

private:
  template <typename Container, typename RandomAccessIterator>
  static void SortImpl(GroupIterator<RandomAccessIterator> first,
                       GroupIterator<RandomAccessIterator> last) {
    std::cout << first.Size() << std::endl;
    typename GroupIterator<RandomAccessIterator>::difference_type size =
        last - first;
    if (size < 2) {
      return;
    }

    bool has_stray = (size % 2);
    GroupIterator<RandomAccessIterator> end = has_stray ? last - 1 : last;

    // Sort in pairs
    for (GroupIterator<RandomAccessIterator> it = first; it != end; it += 2) {
      // std::cout << *it << std::endl;
      if (*it < *(it + 1)) {
        continue;
      }
      std::iter_swap(it, std::next(it.Base()));
    }

    // Recursively sort the pairs
    SortImpl<Container>(GroupIterator<RandomAccessIterator>(first, 2),
                        GroupIterator<RandomAccessIterator>(end, 2));

    // Separate the sorted pairs into chain and pend
    Container chain;
    chain.push_back(first);
    chain.push_back(first + 1);
    Container pend;
    for (GroupIterator<RandomAccessIterator> it = first; it != end; it += 2) {
      chain.push_back(it);
      pend.push_back(it + 1);
    }
    if (has_stray) {
      pend.push_back(last);
    }

    // Insert the pend into the chain
    GroupIterator<RandomAccessIterator> current_it = first;
    typename Container::iterator current_pend = pend.begin();
    for (typename GroupIterator<RandomAccessIterator>::difference_type
             pow2 = 1,
             jn = 0, group = 2;
         group <= pend.end() - current_pend;
         pow2 *= 2, jn = pow2 - jn, group = jn * 2 /* jn*2 is 2^n-1 */) {
      GroupIterator<RandomAccessIterator> it =
          current_it + group * 2; // Multiply by 2 for pairs
      typename Container::iterator pend_it = current_pend;
      while (true) {
        --pend_it;

        // TODO: Binary search for the insertion point

        if (pend_it == current_pend) {
          break;
        }
        it -= 2;
      }

      current_it += group * 2; // Multiply by 2 for pairs
      current_pend += group;
    }
    while (current_pend != pend.end()) {
      // TODO: Binary search for the insertion point

      ++current_pend;
    }

    // TODO: Overwrite the sorted chain into the original container
  }
};

#endif // PMERGE_ME_HPP

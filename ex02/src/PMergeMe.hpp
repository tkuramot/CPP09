#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include "GroupIterator.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <iomanip>

#define VERBOSE 1

#ifdef VERBOSE
#define debug std::cerr
#else
#define debug if(false) std::cerr
#endif

class PMergeMe {
public:
  template <typename T> static void Sort(std::vector<T> &v) {
    SortImpl<std::vector, typename std::vector<T>::iterator>(
        GroupIterator<typename std::vector<T>::iterator>(v.begin(), 1),
        GroupIterator<typename std::vector<T>::iterator>(v.end(), 1));
  }
  template <typename T> static void Sort(std::deque<T> &d) {
    SortImpl<std::vector, typename std::deque<T>::iterator>(
        GroupIterator<typename std::deque<T>::iterator>(d.begin(), 1),
        GroupIterator<typename std::deque<T>::iterator>(d.end(), 1));
  }

private:
  template <template <typename, typename> class Container,
            typename RandomAccessIterator>
  static void SortImpl(GroupIterator<RandomAccessIterator> first,
                       GroupIterator<RandomAccessIterator> last) {
    debug << "===" << std::endl;
    debug << "input: ";
    GroupIterator<RandomAccessIterator>::DebugPrint(first, last);
    typename GroupIterator<RandomAccessIterator>::difference_type size =
        last - first;
    if (size < 2) {
      return;
    }

    bool has_stray = (size % 2);
    GroupIterator<RandomAccessIterator> end = has_stray ? last - 1 : last;

    // Sort in pairs
    debug << "pairing numbers and sorting in pairs..." << std::endl;
    for (GroupIterator<RandomAccessIterator> it = first; it != end; it += 2) {
      debug << "- comparing " << *it << " and " << *(it + 1) << std::endl;
      if (*it < *(it + 1)) {
        continue;
      }
      std::iter_swap(it, (it + 1));
    }

    std::stringstream large, small;
    for (GroupIterator<RandomAccessIterator> it = first; it != end; it += 2) {
      large << std::setw(2) << *(it + 1) << " ";
      small << std::setw(2) << *it << " ";
    }
    if (has_stray) {
      small << std::setw(2) << *(last - 1) << " ";
    }
    debug << "large: " << large.str() << std::endl;
    debug << "small: " << small.str() << std::endl;

    // Recursively sort the pairs
    SortImpl<Container>(GroupIterator<RandomAccessIterator>(first, 2),
                        GroupIterator<RandomAccessIterator>(end, 2));

    // Separate the sorted pairs into chain and pend
    typedef Container<GroupIterator<RandomAccessIterator>,
                      std::allocator<GroupIterator<RandomAccessIterator> > >
        chain_t;
    chain_t chain;
    debug << "===" << std::endl;
    debug << "separating numbers into chain and pend..." << std::endl;
    debug << "inserting first pend element into chain" << std::endl;
    chain.push_back(first);
    chain.push_back(first + 1);
    debug << *chain.front() << " " << *chain.back() << std::endl;
    typedef Container<typename chain_t::iterator,
                      std::allocator<typename chain_t::iterator> >
        pend_t;
    pend_t pend;
    for (GroupIterator<RandomAccessIterator> it = first; it != end; it += 2) {
      typename chain_t::iterator tmp = chain.insert(chain.end(), it);
      pend.emplace_back(tmp);
    }
    if (has_stray) {
      pend.emplace_back(chain.end());
    }

    // Insert the pend into the chain
    GroupIterator<RandomAccessIterator> current_it = first;
    typename pend_t::iterator current_pend = pend.begin();
    for (typename GroupIterator<RandomAccessIterator>::difference_type
             pow2 = 1,
             jn = 0, group = 2;
         group <= pend.end() - current_pend;
         pow2 *= 2, jn = pow2 - jn, group = jn * 2 /* jn*2 is 2^n-1 */) {
      GroupIterator<RandomAccessIterator> it =
          current_it + group * 2; // Multiply by 2 for pairs
      typename pend_t::iterator pend_it = current_pend + group;
      debug << "binary search for " << *it << " in first " << it - current_it - 1 << " of chain" << std::endl;
      while (true) {
        --pend_it;

        typename chain_t::iterator left = chain.begin();
        typename chain_t::iterator right = *pend_it;
        while (left != right) {
          typename chain_t::iterator mid = left + (right - left) / 2;
          debug << "- comparing " << **mid << " and " << *it << std::endl;
          if (**mid < *it) {
            left = mid + 1;
          } else {
            right = mid;
          }
        }
        chain.insert(left, it);

        if (pend_it == current_pend) {
          break;
        }
        it -= 2;
      }

      current_it += group * 2; // Multiply by 2 for pairs
      current_pend += group;
    }
    while (current_pend != pend.end()) {
      current_it += 2;
      typename chain_t::iterator left = chain.begin();
      typename chain_t::iterator right = *current_pend;
      while (left != right) {
        typename chain_t::iterator mid = left + (right - left) / 2;
        if (**mid < *current_it) {
          left = mid + 1;
        } else {
          right = mid;
        }
      }
      chain.insert(left, current_it);

      ++current_pend;
    }

    // Container<RandomAccessIterator, std::allocator<RandomAccessIterator> > cache;
    // for (typename chain_t::iterator it = chain.begin(); it != chain.end(); ++it) {
    //   RandomAccessIterator begin = it->Base();
    //   RandomAccessIterator end = begin + it->Size();
    //   for (RandomAccessIterator i = begin; i != end; ++i) {
    //     cache.push_back(i);
    //   }
    // }
    // std::copy(cache.begin(), cache.end(), first.Base());
  }
};

#endif // PMERGE_ME_HPP

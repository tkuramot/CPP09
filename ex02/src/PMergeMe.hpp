#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <iterator>
#include <iostream>

#ifdef DEBUG_MODE
#define DEBUG(msg) \
  do { \
    std::cerr << "[DEBUG] " << msg << std::endl; \
  } while(0)
#else
#define DEBUG(msg)
#endif

static size_t comparison_count = 0;

class PMergeMe {
  public:
    template <typename T>
    static void Sort(std::vector<T> &vec) {
#ifdef DEBUG_MODE
      comparison_count = 0;
#endif
      GroupIterator<typename std::vector<T>::iterator> first(vec.begin(), 1);
      GroupIterator<typename std::vector<T>::iterator> last(vec.end(), 1);
      SortImplVec<std::vector<T> >(first, last);
#ifdef DEBUG_MODE
      std::cout << "comparison count: " << comparison_count << std::endl;
#endif
    }
    template <typename T>
    static void Sort(std::deque<T> &deq) {
#ifdef DEBUG_MODE
      comparison_count = 0;
#endif
      GroupIterator<typename std::deque<T>::iterator> first(deq.begin(), 1);
      GroupIterator<typename std::deque<T>::iterator> last(deq.end(), 1);
      SortImplDeq<std::deque<T> >(first, last);
#ifdef DEBUG_MODE
      std::cout << "comparison count: " << comparison_count << std::endl;
#endif
    }

  private:
    template <typename Iterator>
    class GroupIterator {
      public:
        typedef Iterator iterator_type;
        typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        typedef typename std::iterator_traits<Iterator>::pointer pointer;
        typedef typename std::iterator_traits<Iterator>::reference reference;
        typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;

        GroupIterator(): it_(), size_(0) {}
        GroupIterator(Iterator it, difference_type size): it_(it), size_(size) {}
        GroupIterator(const GroupIterator &other): it_(other.it_), size_(other.size_) {}
        GroupIterator &operator=(const GroupIterator &other) {
          if (this == &other) { return *this; }
          it_ = other.it_;
          size_ = other.size_;
          return *this;
        }
        ~GroupIterator() {}

        iterator_type base() const { return it_; }
        difference_type size() const { return size_; }

        reference operator*() const {
          Iterator tmp = it_;
          std::advance(tmp, size_ - 1);
          return *tmp;
        }
        pointer operator->() const {
          return  &(operator*());
        }
        GroupIterator &operator++() {
          std::advance(it_, size_);
          return *this;
        }
        GroupIterator &operator--() {
          std::advance(it_, -size_);
          return *this;
        }
        GroupIterator operator+(difference_type n) {
          GroupIterator tmp = *this;
          tmp += n;
          return tmp;
        }
        GroupIterator operator-(difference_type n) {
          GroupIterator tmp = *this;
          tmp -= n;
          return tmp;
        }
        GroupIterator &operator+=(difference_type n) {
          it_ += size_ * n;
          return *this;
        }
        GroupIterator &operator-=(difference_type n) {
          it_ -= size_ * n;
          return *this;
        }
        difference_type operator-(const GroupIterator &rhs) const {
          return (it_ - rhs.it_) / size_;
        }

        bool operator==(const GroupIterator &rhs) const {
          return it_ == rhs.it_;
        }
        bool operator!=(const GroupIterator &rhs) const {
          return it_ != rhs.it_;
        }
        bool operator<(const GroupIterator &rhs) const {
          return it_ < rhs.it_;
        }
        bool operator>(const GroupIterator &rhs) const {
          return it_ > rhs.it_;
        }
        void iterSwap(GroupIterator other) {
          for (difference_type i = 0; i < size_; ++i) {
            std::iter_swap(it_ + i, other.it_ + i);
          }
        }
      private:
        Iterator it_;
        difference_type size_;
    };

    PMergeMe();
    PMergeMe(const PMergeMe &other);
    PMergeMe &operator=(const PMergeMe &other);
    ~PMergeMe();

    template <typename T>
    static T ValueInGroupIterator(T v) {
      return v;
    }
    template <typename Iterator>
    static typename Iterator::value_type ValueInGroupIterator(GroupIterator<Iterator> it) {
      if (it.size() == 1) { return *it; }
      return ValueInGroupIterator(*it);
    }
    template <typename Iterator>
    static void ListGroupIterators(GroupIterator<Iterator> first, GroupIterator<Iterator> last) {
      for (GroupIterator<Iterator> it = first; it != last; ++it) {
        std::cerr << ValueInGroupIterator(it) << " ";
      }
      std::cerr << std::endl;
    }
    template <typename Container>
    static void ListContainer(Container c) {
      for (size_t i = 0; i < c.size(); ++i) {
        std::cerr << ValueInGroupIterator(c[i]) << " ";
      }
      std::cerr << std::endl;
    }

    template <typename Container>
    static void BinaryInsertion(Container &chain, typename Container::value_type elem, size_t right) {
      size_t left = 0;
      if (chain.size() <= right) { right = chain.size() - 1; }

      size_t mid = left + (right - left) / 2;
      while (mid > 0 && left <= right) {
        mid = left + (right - left) / 2;
#ifdef DEBUG_MODE
        ++comparison_count;
        DEBUG("comparing " << ValueInGroupIterator(chain[mid]) << " and " << ValueInGroupIterator(elem));
#endif
        if (ValueInGroupIterator(chain[mid]) == ValueInGroupIterator(elem)) {
          left = mid;
          break;
        } else if (ValueInGroupIterator(chain[mid]) < ValueInGroupIterator(elem)) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }
      chain.insert(chain.begin() + left, elem);
    }

    template <typename Container>
    static void Insertion(Container &main_chain, Container &pend_chain) {
      size_t total_elem = main_chain.size() + pend_chain.size();

      size_t num_inserted = 1;
      size_t prev_group_size = 0;
      size_t curr_group_size = 2;
      size_t upper_bound = total_elem - 1 < 4 ? total_elem - 1 : 3;

      while (num_inserted + curr_group_size < pend_chain.size()) {
        size_t index = num_inserted + curr_group_size - 1;
        while (index >= num_inserted) {
#ifdef DEBUG_MODE
          DEBUG("main chain: ");
          ListContainer(main_chain);
          DEBUG("pend chain: "); ListContainer(pend_chain);
          DEBUG("inserting " << ValueInGroupIterator(pend_chain[index]) << " with upper_bound: " << upper_bound -1);
#endif
          BinaryInsertion(main_chain, pend_chain[index], upper_bound - 1);
          --index;
        }

        num_inserted += curr_group_size;
        size_t next_group_size = curr_group_size + 2 * prev_group_size;
        prev_group_size = curr_group_size;
        curr_group_size = next_group_size;
        upper_bound = 2 * upper_bound + 1;
      }

      if (!pend_chain.size()) { return; }
      for (size_t index = pend_chain.size() - 1; index >= num_inserted; --index) {
        BinaryInsertion(main_chain, pend_chain[index], upper_bound - 1);
      }
    }

    template <typename Container>
    static void SortImplVec(GroupIterator<typename Container::iterator> first, GroupIterator<typename Container::iterator> last) {
      typedef GroupIterator<typename Container::iterator> group_iter;

#ifdef DEBUG_MODE
      DEBUG("SortImpl called with iter size " << first.size());
      DEBUG("Sorting following elements");
      ListGroupIterators(first, last);
#endif
      typename group_iter::difference_type size = std::distance(first, last);
      if (size < 2) { return; }

      bool has_stray = (size % 2 == 1);
      group_iter end = has_stray ? last - 1 : last;
      for (group_iter it = first; it != end; it += 2) {
#ifdef DEBUG_MODE
        ++comparison_count;
#endif
        if (*it > *(it + 1)) {
          it.iterSwap(it + 1);
        }
      }

      SortImplVec<Container>(group_iter(first.base(), 2 * first.size()), group_iter(end.base(), 2 * end.size()));

      std::vector<group_iter> main_chain;
      main_chain.push_back(first);
      main_chain.push_back(first + 1);
      std::vector<group_iter> pend_chain;
      pend_chain.push_back(first);
      for (group_iter it = first + 2; it != end; it += 2) {
        main_chain.push_back(it + 1);
        pend_chain.push_back(it);
      }
      if (has_stray) { pend_chain.push_back(end); }

#ifdef DEBUG_MODE
      DEBUG("Inerting elements. iter size: " << first.size());
#endif
      Insertion(main_chain, pend_chain);
#ifdef DEBUG_MODE
      ListContainer(main_chain);
      DEBUG("Insertion completed");
#endif
      
      std::vector<typename group_iter::value_type> tmp;
      for (typename std::vector<group_iter>::iterator it = main_chain.begin(); it != main_chain.end(); ++it) {
        for (typename group_iter::difference_type i = 0; i < it->size(); ++i) {
          tmp.push_back(*(it->base() + i));
        }
      }
      std::copy(tmp.begin(), tmp.end(), first.base());
    }

    template <typename Container>
    static void SortImplDeq(GroupIterator<typename Container::iterator> first, GroupIterator<typename Container::iterator> last) {
      typedef GroupIterator<typename Container::iterator> group_iter;

#ifdef DEBUG_MODE
      DEBUG("SortImpl called with iter size " << first.size());
      DEBUG("Sorting following elements");
      ListGroupIterators(first, last);
#endif
      typename group_iter::difference_type size = std::distance(first, last);
      if (size < 2) { return; }

      bool has_stray = (size % 2 == 1);
      group_iter end = has_stray ? last - 1 : last;
      for (group_iter it = first; it != end; it += 2) {
#ifdef DEBUG_MODE
        ++comparison_count;
#endif
        if (*it > *(it + 1)) {
          it.iterSwap(it + 1);
        }
      }

      SortImplDeq<Container>(group_iter(first.base(), 2 * first.size()), group_iter(end.base(), 2 * end.size()));

      std::deque<group_iter> main_chain;
      main_chain.push_back(first);
      main_chain.push_back(first + 1);
      std::deque<group_iter> pend_chain;
      pend_chain.push_back(first);
      for (group_iter it = first + 2; it != end; it += 2) {
        main_chain.push_back(it + 1);
        pend_chain.push_back(it);
      }
      if (has_stray) { pend_chain.push_back(end); }

#ifdef DEBUG_MODE
      DEBUG("Inerting elements. iter size: " << first.size());
#endif
      Insertion(main_chain, pend_chain);
#ifdef DEBUG_MODE
      ListContainer(main_chain);
      DEBUG("Insertion completed");
#endif
      
      std::deque<typename group_iter::value_type> tmp;
      for (typename std::deque<group_iter>::iterator it = main_chain.begin(); it != main_chain.end(); ++it) {
        for (typename group_iter::difference_type i = 0; i < it->size(); ++i) {
          tmp.push_back(*(it->base() + i));
        }
      }
      std::copy(tmp.begin(), tmp.end(), first.base());
    }
};

#endif

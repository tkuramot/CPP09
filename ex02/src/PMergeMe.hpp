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

// Helper: get iterator traits for C++98
template<typename Iterator>
struct iterator_traits {
	typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
	typedef typename std::iterator_traits<Iterator>::pointer pointer;
	typedef typename std::iterator_traits<Iterator>::reference reference;
};

// group_iterator: groups elements for Ford-Johnson algorithm
template<typename Iterator>
class group_iterator {
public:
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

	// Constructors
	group_iterator() : _it(), _size(0) {}
	group_iterator(Iterator it, difference_type size) : _it(it), _size(size) {}

	// Access
	iterator_type base() const { return _it; }
	difference_type size() const { return _size; }

	// Element access - returns last element of the group
	reference operator*() const {
		Iterator tmp = _it;
		std::advance(tmp, _size - 1);
		return *tmp;
	}

	pointer operator->() const {
		return &(operator*());
	}

	// Increment/decrement
	group_iterator& operator++() {
		std::advance(_it, _size);
		return *this;
	}

	group_iterator operator++(int) {
		group_iterator tmp = *this;
		++(*this);
		return tmp;
	}

	group_iterator& operator--() {
		std::advance(_it, -_size);
		return *this;
	}

	group_iterator operator--(int) {
		group_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	group_iterator& operator+=(difference_type n) {
		_it += _size * n;
		return *this;
	}

	group_iterator& operator-=(difference_type n) {
		_it -= _size * n;
		return *this;
	}

	// Comparison operators
	friend bool operator==(const group_iterator& lhs, const group_iterator& rhs) {
		return lhs.base() == rhs.base();
	}

	friend bool operator!=(const group_iterator& lhs, const group_iterator& rhs) {
		return lhs.base() != rhs.base();
	}

	friend bool operator<(const group_iterator& lhs, const group_iterator& rhs) {
		return lhs.base() < rhs.base();
	}

	friend bool operator<=(const group_iterator& lhs, const group_iterator& rhs) {
		return lhs.base() <= rhs.base();
	}

	friend bool operator>(const group_iterator& lhs, const group_iterator& rhs) {
		return lhs.base() > rhs.base();
	}

	friend bool operator>=(const group_iterator& lhs, const group_iterator& rhs) {
		return lhs.base() >= rhs.base();
	}

	// Arithmetic operators
	friend group_iterator operator+(group_iterator it, difference_type n) {
		it += n;
		return it;
	}

	friend group_iterator operator+(difference_type n, group_iterator it) {
		it += n;
		return it;
	}

	friend group_iterator operator-(group_iterator it, difference_type n) {
		it -= n;
		return it;
	}

	friend difference_type operator-(const group_iterator& lhs, const group_iterator& rhs) {
		return (lhs.base() - rhs.base()) / lhs.size();
	}

private:
	Iterator _it;
	difference_type _size;
};

// iter_swap for group_iterator
template<typename Iterator>
void iter_swap(group_iterator<Iterator> lhs, group_iterator<Iterator> rhs) {
	Iterator lhs_begin = lhs.base();
	Iterator lhs_end = lhs.base();
	std::advance(lhs_end, lhs.size());
	Iterator rhs_begin = rhs.base();

	std::swap_ranges(lhs_begin, lhs_end, rhs_begin);
}

// Helper: conditional swap
template<typename Iterator>
void iter_swap_if(Iterator a, Iterator b) {
	if (*b < *a) {
		std::iter_swap(a, b);
	}
}

template<typename Iterator>
void iter_swap_if(group_iterator<Iterator> a, group_iterator<Iterator> b) {
	if (*b < *a) {
		iter_swap(a, b);
	}
}

// Helper: custom upper_bound for list of group_iterators
// Compares value with dereferenced elements in the list
template<typename ListIter, typename GroupIter>
ListIter custom_upper_bound(ListIter first, ListIter last, const GroupIter& value_iter) {
	ListIter it;
	typename std::iterator_traits<ListIter>::difference_type count, step;
	count = std::distance(first, last);

	while (count > 0) {
		it = first;
		step = count / 2;
		std::advance(it, step);

		// Compare dereferenced values
		if (!(*value_iter < **it)) {
			first = ++it;
			count -= step + 1;
		} else {
			count = step;
		}
	}
	return first;
}

class PMergeMe {
public:
	PMergeMe(int argc, char **argv);
	~PMergeMe();

	void sortAndDisplay();

private:
	std::vector<int> _vec;
	std::deque<int> _deq;
	std::vector<int> _original;

	// Parsing
	void parseArguments(int argc, char **argv);
	int parsePositiveInt(const std::string& str);

	// Ford-Johnson sort for vector
	void mergeInsertionSortVector(std::vector<int>::iterator first,
	                               std::vector<int>::iterator last);
	void mergeInsertionSortVectorImpl(group_iterator<std::vector<int>::iterator> first,
	                                   group_iterator<std::vector<int>::iterator> last);

	// Ford-Johnson sort for deque
	void mergeInsertionSortDeque(std::deque<int>::iterator first,
	                              std::deque<int>::iterator last);
	void mergeInsertionSortDequeImpl(group_iterator<std::deque<int>::iterator> first,
	                                  group_iterator<std::deque<int>::iterator> last);

	// Display
	void displaySequence(const std::string& prefix, const std::vector<int>& container);
	void displayTime(const std::string& containerName, size_t size, double microseconds);

	// Timing
	double getTimeDifference(struct timeval start, struct timeval end);

	// No copy
	PMergeMe(const PMergeMe&);
	PMergeMe& operator=(const PMergeMe&);
};

#endif

#include "PMergeMe.hpp"
#include <stdexcept>
#include <limits>
#include <iomanip>

PMergeMe::PMergeMe(int argc, char **argv) {
	parseArguments(argc, argv);
}

PMergeMe::~PMergeMe() {}

void PMergeMe::parseArguments(int argc, char **argv) {
	if (argc < 2) {
		throw std::runtime_error("Error: No arguments provided");
	}

	for (int i = 1; i < argc; ++i) {
		int num = parsePositiveInt(argv[i]);
		_original.push_back(num);
		_vec.push_back(num);
		_deq.push_back(num);
	}
}

int PMergeMe::parsePositiveInt(const std::string& str) {
	if (str.empty()) {
		throw std::runtime_error("Error");
	}

	for (size_t i = 0; i < str.length(); ++i) {
		if (!std::isdigit(str[i])) {
			throw std::runtime_error("Error");
		}
	}

	std::istringstream iss(str);
	long num;
	iss >> num;

	if (iss.fail() || num < 0 || num > std::numeric_limits<int>::max()) {
		throw std::runtime_error("Error");
	}

	return static_cast<int>(num);
}

void PMergeMe::displaySequence(const std::string& prefix, const std::vector<int>& container) {
	std::cout << prefix;

	size_t size = container.size();

	for (size_t i = 0; i < size; ++i) {
		std::cout << container[i];
		if (i + 1 < size) {
			std::cout << " ";
		}
	}

	std::cout << std::endl;
}

void PMergeMe::displayTime(const std::string& containerName, size_t size, double microseconds) {
	std::cout << "Time to process a range of " << size
	          << " elements with " << containerName << " : "
	          << std::fixed << std::setprecision(5) << microseconds << " us"
	          << std::endl;
}

double PMergeMe::getTimeDifference(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
}

void PMergeMe::sortAndDisplay() {
	displaySequence("Before: ", _original);

	struct timeval start_vec, end_vec;
	gettimeofday(&start_vec, NULL);
	mergeInsertionSortVector(_vec.begin(), _vec.end());
	gettimeofday(&end_vec, NULL);
	double time_vec = getTimeDifference(start_vec, end_vec);

	struct timeval start_deq, end_deq;
	gettimeofday(&start_deq, NULL);
	mergeInsertionSortDeque(_deq.begin(), _deq.end());
	gettimeofday(&end_deq, NULL);
	double time_deq = getTimeDifference(start_deq, end_deq);

	displaySequence("After:  ", _vec);
	displayTime("std::vector", _vec.size(), time_vec);
	displayTime("std::deque", _deq.size(), time_deq);
}

// ============================================================================
// Ford-Johnson Algorithm for std::vector
// ============================================================================

void PMergeMe::mergeInsertionSortVector(std::vector<int>::iterator first,
                                         std::vector<int>::iterator last) {
	std::vector<int>::difference_type size = std::distance(first, last);
	if (size < 2) {
		return;
	}

	mergeInsertionSortVectorImpl(
		group_iterator<std::vector<int>::iterator>(first, 1),
		group_iterator<std::vector<int>::iterator>(last, 1)
	);
}

void PMergeMe::mergeInsertionSortVectorImpl(
	group_iterator<std::vector<int>::iterator> first,
	group_iterator<std::vector<int>::iterator> last) {

	typedef group_iterator<std::vector<int>::iterator> group_iter;
	typedef std::vector<int>::difference_type diff_t;

	diff_t size = last - first;
	if (size < 2) return;

	// Step 1: Pair and swap
	bool has_stray = (size % 2 != 0);
	group_iter end = has_stray ? last - 1 : last;

	for (group_iter it = first; it != end; it += 2) {
		iter_swap_if(it, it + 1);
	}

	// Step 2: Recursively sort pairs by max
	mergeInsertionSortVectorImpl(
		group_iter(first.base(), 2 * first.size()),
		group_iter(end.base(), 2 * end.size())
	);

	// Step 3: Separate main chain and pend
	std::list<group_iter> chain;
	chain.push_back(first);
	chain.push_back(first + 1);

	std::vector<std::list<group_iter>::iterator> pend;

	for (group_iter it = first + 2; it != end; it += 2) {
		std::list<group_iter>::iterator inserted = chain.insert(chain.end(), it + 1);
		pend.push_back(inserted);
	}

	if (has_stray) {
		pend.push_back(chain.end());
	}

	// Step 4: Insert pend elements using Jacobsthal sequence
	group_iter current_it = first;
	std::vector<std::list<group_iter>::iterator>::iterator current_pend = pend.begin();

	for (diff_t pow2 = 1, jn = 0, dist = 2;
	     dist <= static_cast<diff_t>(pend.end() - current_pend);
	     pow2 *= 2, jn = pow2 - jn, dist = 2 * jn) {

		group_iter it = current_it + dist * 2;
		std::vector<std::list<group_iter>::iterator>::iterator pe = current_pend + dist;

		while (true) {
			--pe;

			std::list<group_iter>::iterator insertion_point =
				custom_upper_bound(chain.begin(), *pe, it);
			chain.insert(insertion_point, it);

			if (pe == current_pend) break;
			it -= 2;
		}

		current_it += dist * 2;
		current_pend += dist;
	}

	// Step 5: Insert remaining pend elements
	while (current_pend != pend.end()) {
		current_it += 2;
		std::list<group_iter>::iterator insertion_point =
			custom_upper_bound(chain.begin(), *current_pend, current_it);
		chain.insert(insertion_point, current_it);
		++current_pend;
	}

	// Step 6: Move sorted elements to cache then back
	std::vector<int> cache;
	cache.reserve(size * first.size());

	for (std::list<group_iter>::iterator it = chain.begin(); it != chain.end(); ++it) {
		std::vector<int>::iterator begin = it->base();
		std::vector<int>::iterator end = it->base();
		std::advance(end, it->size());
		cache.insert(cache.end(), begin, end);
	}

	std::copy(cache.begin(), cache.end(), first.base());
}

// ============================================================================
// Ford-Johnson Algorithm for std::deque
// ============================================================================

void PMergeMe::mergeInsertionSortDeque(std::deque<int>::iterator first,
                                        std::deque<int>::iterator last) {
	std::deque<int>::difference_type size = std::distance(first, last);
	if (size < 2) {
		return;
	}

	mergeInsertionSortDequeImpl(
		group_iterator<std::deque<int>::iterator>(first, 1),
		group_iterator<std::deque<int>::iterator>(last, 1)
	);
}

void PMergeMe::mergeInsertionSortDequeImpl(
	group_iterator<std::deque<int>::iterator> first,
	group_iterator<std::deque<int>::iterator> last) {

	typedef group_iterator<std::deque<int>::iterator> group_iter;
	typedef std::deque<int>::difference_type diff_t;

	diff_t size = last - first;
	if (size < 2) return;

	// Step 1: Pair and swap
	bool has_stray = (size % 2 != 0);
	group_iter end = has_stray ? last - 1 : last;

	for (group_iter it = first; it != end; it += 2) {
		iter_swap_if(it, it + 1);
	}

	// Step 2: Recursively sort pairs by max
	mergeInsertionSortDequeImpl(
		group_iter(first.base(), 2 * first.size()),
		group_iter(end.base(), 2 * end.size())
	);

	// Step 3: Separate main chain and pend
	std::list<group_iter> chain;
	chain.push_back(first);
	chain.push_back(first + 1);

	std::vector<std::list<group_iter>::iterator> pend;

	for (group_iter it = first + 2; it != end; it += 2) {
		std::list<group_iter>::iterator inserted = chain.insert(chain.end(), it + 1);
		pend.push_back(inserted);
	}

	if (has_stray) {
		pend.push_back(chain.end());
	}

	// Step 4: Insert pend elements using Jacobsthal sequence
	group_iter current_it = first;
	std::vector<std::list<group_iter>::iterator>::iterator current_pend = pend.begin();

	for (diff_t pow2 = 1, jn = 0, dist = 2;
	     dist <= static_cast<diff_t>(pend.end() - current_pend);
	     pow2 *= 2, jn = pow2 - jn, dist = 2 * jn) {

		group_iter it = current_it + dist * 2;
		std::vector<std::list<group_iter>::iterator>::iterator pe = current_pend + dist;

		while (true) {
			--pe;

			std::list<group_iter>::iterator insertion_point =
				custom_upper_bound(chain.begin(), *pe, it);
			chain.insert(insertion_point, it);

			if (pe == current_pend) break;
			it -= 2;
		}

		current_it += dist * 2;
		current_pend += dist;
	}

	// Step 5: Insert remaining pend elements
	while (current_pend != pend.end()) {
		current_it += 2;
		std::list<group_iter>::iterator insertion_point =
			custom_upper_bound(chain.begin(), *current_pend, current_it);
		chain.insert(insertion_point, current_it);
		++current_pend;
	}

	// Step 6: Move sorted elements to cache then back
	std::deque<int> cache;

	for (std::list<group_iter>::iterator it = chain.begin(); it != chain.end(); ++it) {
		std::deque<int>::iterator begin = it->base();
		std::deque<int>::iterator end = it->base();
		std::advance(end, it->size());
		cache.insert(cache.end(), begin, end);
	}

	std::copy(cache.begin(), cache.end(), first.base());
}

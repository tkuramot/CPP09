#include "PMergeMe.hpp"

// ============================================================================
// Ford-Johnson Algorithm for std::vector
// ============================================================================

void PMergeMe::sort(std::vector<int>::iterator first,
                    std::vector<int>::iterator last) {
	std::vector<int>::difference_type size = std::distance(first, last);
	if (size < 2) {
		return;
	}

	sortImpl(
		group_iterator<std::vector<int>::iterator>(first, 1),
		group_iterator<std::vector<int>::iterator>(last, 1)
	);
}

void PMergeMe::sortImpl(
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
	sortImpl(
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

void PMergeMe::sort(std::deque<int>::iterator first,
                    std::deque<int>::iterator last) {
	std::deque<int>::difference_type size = std::distance(first, last);
	if (size < 2) {
		return;
	}

	sortImpl(
		group_iterator<std::deque<int>::iterator>(first, 1),
		group_iterator<std::deque<int>::iterator>(last, 1)
	);
}

void PMergeMe::sortImpl(
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
	sortImpl(
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

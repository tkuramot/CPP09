#include "PMergeMe.hpp"

PMergeMe::PMergeMe() {}

PMergeMe::PMergeMe(const PMergeMe &other) {
  (void) other;
}

PMergeMe &PMergeMe::operator=(const PMergeMe &other) {
  if (this == &other) {
    return *this;
  }
  return *this;
}

PMergeMe::~PMergeMe() {}

void PMergeMe::sort(std::vector<int>::iterator first,
                    std::vector<int>::iterator last)
{
  std::vector<int>::difference_type size = std::distance(first, last);
  if (size < 2)
  {
    return;
  }

  sortImpl(
      GroupIterator<std::vector<int>::iterator>(first, 1),
      GroupIterator<std::vector<int>::iterator>(last, 1));
}

void PMergeMe::sortImpl(
    GroupIterator<std::vector<int>::iterator> first,
    GroupIterator<std::vector<int>::iterator> last)
{

  typedef GroupIterator<std::vector<int>::iterator> group_iter;
  typedef std::vector<int>::difference_type diff_t;

  diff_t size = last - first;
  if (size < 2)
    return;

  bool has_stray = (size % 2 != 0);
  group_iter end = has_stray ? last - 1 : last;

  for (group_iter it = first; it != end; it += 2)
  {
    iterSwapIf(it, it + 1);
  }

  sortImpl(
      group_iter(first.base(), 2 * first.size()),
      group_iter(end.base(), 2 * end.size()));

  std::vector<group_iter> chain;
  chain.reserve(size);
  chain.push_back(first);
  chain.push_back(first + 1);

  std::vector<diff_t> pend;
  pend.reserve((size + 1) / 2 - 1 + (has_stray ? 1 : 0));

  for (group_iter it = first + 2; it != end; it += 2)
  {
    chain.push_back(it + 1);
    pend.push_back(chain.size() - 1);
  }

  if (has_stray)
  {
    pend.push_back(chain.size());
  }

  group_iter current_it = first;
  std::vector<diff_t>::iterator current_pend = pend.begin();

  for (diff_t pow2 = 1, jn = 0, dist = 2;
       dist <= static_cast<diff_t>(pend.end() - current_pend);
       pow2 *= 2, jn = pow2 - jn, dist = 2 * jn)
  {

    group_iter it = current_it + dist * 2;
    std::vector<diff_t>::iterator pe = current_pend + dist;

    while (true)
    {
      --pe;

      diff_t insertion_index =
          binarySearchInsertionPoint(chain.begin(), chain.begin() + *pe, it) - chain.begin();
      chain.insert(chain.begin() + insertion_index, it);

      for (std::vector<diff_t>::iterator idx = current_pend; idx != pend.end(); ++idx)
      {
        if (*idx >= insertion_index)
          ++(*idx);
      }

      if (pe == current_pend)
        break;
      it -= 2;
    }

    current_it += dist * 2;
    current_pend += dist;
  }

  while (current_pend != pend.end())
  {
    current_it += 2;
    diff_t insertion_index =
        binarySearchInsertionPoint(chain.begin(), chain.begin() + *current_pend, current_it) - chain.begin();
    chain.insert(chain.begin() + insertion_index, current_it);

    for (std::vector<diff_t>::iterator idx = current_pend + 1; idx != pend.end(); ++idx)
    {
      if (*idx >= insertion_index)
        ++(*idx);
    }
    ++current_pend;
  }

  std::vector<int> cache;
  cache.reserve(size * first.size());

  for (std::vector<group_iter>::iterator it = chain.begin(); it != chain.end(); ++it)
  {
    std::vector<int>::iterator begin = it->base();
    std::vector<int>::iterator end = it->base();
    std::advance(end, it->size());
    cache.insert(cache.end(), begin, end);
  }

  std::copy(cache.begin(), cache.end(), first.base());
}

void PMergeMe::sort(std::deque<int>::iterator first,
                    std::deque<int>::iterator last)
{
  std::deque<int>::difference_type size = std::distance(first, last);
  if (size < 2)
  {
    return;
  }

  sortImpl(
      GroupIterator<std::deque<int>::iterator>(first, 1),
      GroupIterator<std::deque<int>::iterator>(last, 1));
}

void PMergeMe::sortImpl(
    GroupIterator<std::deque<int>::iterator> first,
    GroupIterator<std::deque<int>::iterator> last)
{

  typedef GroupIterator<std::deque<int>::iterator> group_iter;
  typedef std::deque<int>::difference_type diff_t;

  diff_t size = last - first;
  if (size < 2)
    return;

  bool has_stray = (size % 2 != 0);
  group_iter end = has_stray ? last - 1 : last;

  for (group_iter it = first; it != end; it += 2)
  {
    iterSwapIf(it, it + 1);
  }

  sortImpl(
      group_iter(first.base(), 2 * first.size()),
      group_iter(end.base(), 2 * end.size()));

  std::deque<group_iter> chain;
  chain.push_back(first);
  chain.push_back(first + 1);

  std::vector<diff_t> pend;
  pend.reserve((size + 1) / 2 - 1 + (has_stray ? 1 : 0));

  for (group_iter it = first + 2; it != end; it += 2)
  {
    chain.push_back(it + 1);
    pend.push_back(chain.size() - 1);
  }

  if (has_stray)
  {
    pend.push_back(chain.size());
  }

  group_iter current_it = first;
  std::vector<diff_t>::iterator current_pend = pend.begin();

  for (diff_t pow2 = 1, jn = 0, dist = 2;
       dist <= static_cast<diff_t>(pend.end() - current_pend);
       pow2 *= 2, jn = pow2 - jn, dist = 2 * jn)
  {

    group_iter it = current_it + dist * 2;
    std::vector<diff_t>::iterator pe = current_pend + dist;

    while (true)
    {
      --pe;

      diff_t insertion_index =
          binarySearchInsertionPoint(chain.begin(), chain.begin() + *pe, it) - chain.begin();
      chain.insert(chain.begin() + insertion_index, it);

      for (std::vector<diff_t>::iterator idx = current_pend; idx != pend.end(); ++idx)
      {
        if (*idx >= insertion_index)
          ++(*idx);
      }

      if (pe == current_pend)
        break;
      it -= 2;
    }

    current_it += dist * 2;
    current_pend += dist;
  }

  while (current_pend != pend.end())
  {
    current_it += 2;
    diff_t insertion_index =
        binarySearchInsertionPoint(chain.begin(), chain.begin() + *current_pend, current_it) - chain.begin();
    chain.insert(chain.begin() + insertion_index, current_it);

    for (std::vector<diff_t>::iterator idx = current_pend + 1; idx != pend.end(); ++idx)
    {
      if (*idx >= insertion_index)
        ++(*idx);
    }
    ++current_pend;
  }

  std::deque<int> cache;

  for (std::deque<group_iter>::iterator it = chain.begin(); it != chain.end(); ++it)
  {
    std::deque<int>::iterator begin = it->base();
    std::deque<int>::iterator end = it->base();
    std::advance(end, it->size());
    cache.insert(cache.end(), begin, end);
  }

  std::copy(cache.begin(), cache.end(), first.base());
}

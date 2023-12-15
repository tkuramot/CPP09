//
// Created by k.t. on 2023/12/12.
//

#ifndef A_OUT__MUTANTSTACK_HPP_
#define A_OUT__MUTANTSTACK_HPP_

#include <deque>
#include <stack>

template <typename T> class MutantStack : public std::stack<T> {
public:
  typedef typename std::stack<T>::container_type::iterator iterator;

  MutantStack();
  ~MutantStack();
  MutantStack(const MutantStack &mutant_stack);
  MutantStack &operator=(const MutantStack &mutant_stack);

  iterator begin();
  iterator end();
  iterator rbegin();
  iterator rend();
};

#endif // A_OUT__MUTANTSTACK_HPP_

#include "MutantStack.hpp"

template <typename T> MutantStack<T>::MutantStack() : std::stack<T>() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &mutant_stack)
    : std::stack<T>(mutant_stack) {}

template <typename T> MutantStack<T>::~MutantStack() {}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack &mutant_stack) {
  if (this != &mutant_stack) {
    std::stack<T>::operator=(mutant_stack);
  }
  return *this;
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
  return this->c.begin();
}

template <typename T> typename MutantStack<T>::iterator MutantStack<T>::end() {
  return this->c.end();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::rbegin() {
  return this->c.rbegin();
}

template <typename T> typename MutantStack<T>::iterator MutantStack<T>::rend() {
  return this->c.rend();
}

//
// Created by k.t. on 2023/12/06.
//

#include "easyfind.hpp"
#include <iostream>
#include <list>
#include <vector>

int main() {
  {
    std::cout << "----------------list----------------" << std::endl;
    std::list<int> lst;
    for (int i = 0; i < 10; ++i) {
      std::cout << i << " ";
      lst.push_back(i);
    }
    std::cout << std::endl;
    {
      int target = 5;
      std::list<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
    {
      int target = 100;
      std::list<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
    {
      int target = 9;
      std::list<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
  }
  {
    std::cout << "----------------vector----------------" << std::endl;
    std::vector<int> lst;
    for (int i = 0; i < 10; ++i) {
      std::cout << i << " ";
      lst.push_back(i);
    }
    std::cout << std::endl;
    {
      int target = 5;
      std::vector<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
    {
      int target = 100;
      std::vector<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
    {
      int target = 9;
      std::vector<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
  }
  {
    std::cout << "----------------vector----------------" << std::endl;
    std::vector<int> lst;
    for (int i = 0; i < 10; ++i) {
      std::cout << i << " ";
      lst.push_back(i);
    }
    std::cout << std::endl;
    {
      int target = 5;
      std::vector<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
    {
      int target = 100;
      std::vector<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
    {
      int target = 9;
      std::vector<int>::const_iterator itr = Easyfind(lst, target);
      if (itr == lst.end()) {
        std::cout << target << " not found" << std::endl;
      } else {
        std::cout << target << " found" << std::endl;
      }
    }
  }
  return 0;
}
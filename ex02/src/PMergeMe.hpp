#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

template <typename Container> class PMergeMe {
public:
  static Container sort(Container &c) {
    if (c.size() < 2)
      return c;

    bool has_stray = c.size() % 2;
  }

private:
};

#endif // PMERGE_ME_HPP

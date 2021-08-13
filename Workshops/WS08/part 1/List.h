#ifndef SDDS_LIST_H
#define SDDS_LIST_H
// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace sdds {
template <typename T> class List {
  std::vector<T> list;

public:
  List() {}
  List(const char *fn) {
    std::ifstream file(fn);
    if (!file)
      throw std::string("*** Failed to open file ") + std::string(fn) +
          std::string(" ***");
    while (file) {
      T e;
      if (e.load(file))
        list.push_back(T(e));
    }
  }
  size_t size() const { return list.size(); }
  const T &operator[](size_t i) const { return list[i]; }

  //  Overload the += operator with a raw pointer
  //       as a second operand.
  void operator+=(T *item) { list.push_back(std::move(*item)); }

  void display(std::ostream &os) const {
    os << std::fixed << std::setprecision(2);
    for (auto &e : list)
      e.display(os);
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &l) {
  l.display(os);
  return os;
}
} // namespace sdds
#endif

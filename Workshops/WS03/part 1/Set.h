#ifndef SDDS_SET_H
#define SDDS_SET_H

#include <cstddef>
using std::size_t;

namespace sdds {

template <size_t N, class T> class Set {
public:
  Set();
  Set(Set &&) = default;
  Set(const Set &) = default;
  Set &operator=(Set &&) = default;
  Set &operator=(const Set &) = default;
  ~Set() = default;

  size_t size() const;
  const T &get(size_t idx) const;
  void operator+=(const T &item);

private:
  T arr[N];
  size_t count;

}; // class

template <size_t N, class T> Set<N, T>::Set() { count = 0; }

template <size_t N, class T> size_t Set<N, T>::size() const { return count; }
template <size_t N, class T> const T &Set<N, T>::get(size_t idx) const {
  return arr[idx];
}

template <size_t N, class T> void Set<N, T>::operator+=(const T &item) {
  if (count < N) {
    arr[count] = item;
    count++;
  }
}

} // namespace sdds

#endif // !SDDS_SET_H

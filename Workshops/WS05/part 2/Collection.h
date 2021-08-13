#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <ostream>
#include <string>

using std::ostream;
using std::string;

namespace sdds {
template <class T> // a
class Collection {
public:
  Collection() {
    _cap = 0;
    _items = nullptr;
    _size = 0;
    _observer = nullptr;
  };
  Collection(const std::string &name) : Collection() { _name = name; }
  Collection(Collection &&) = default;
  Collection(const Collection &) = delete;
  Collection &operator=(Collection &&) = default;
  Collection &operator=(const Collection &) = delete;
  ~Collection() {
    if (_cap) {
      delete[] _items;
      _items = nullptr;
    }
  }
  const std::string &name() const { return _name; }
  size_t size() const { return _size; }
  void setObserver(void (*observer)(const Collection<T> &, const T &)) {
    _observer = observer;
  }
  Collection<T> &operator+=(const T &item);
  T &operator[](size_t idx) const;
  T *operator[](const std::string &title) const;

private:
  string _name;
  T *_items;
  size_t _cap;
  size_t _size;
  void (*_observer)(const Collection<T> &, const T &);
};

template <class T> // a
Collection<T> &Collection<T>::operator+=(const T &item) {
  if (!_cap) {
    _cap += 5;
    _items = new T[_cap];
  }

  if ((*this)[item.title()] == nullptr) {
    if (_size >= _cap) {
      _cap *= 2;
      T *temp = new T[_cap];
      for (size_t i = 0; i < _size; i++) {
        temp[i] = _items[i];
      }
      delete[] _items;
      _items = temp;
    }
    _items[_size] = item;
    _size++;
    if (_observer) {
      _observer(*this, item);
    }
  }

  return *this;
}

template <class T> // a
T &Collection<T>::operator[](size_t idx) const {
  if (idx >= _size) {
    throw std::out_of_range("Bad index [" + std::to_string(idx) +
                            "]. Collection has [" + std::to_string(_size) +
                            "] items.");
  }
  return _items[idx];
}

template <class T> // a
T *Collection<T>::operator[](const std::string &title) const {

  size_t i = 0;
  T *ret = nullptr;
  while (i < _size && _items[i].title() != title) {
    i++;
  }
  if (i < _size) {
    ret = &_items[i];
  }
  return ret;
}

template <class T> // a
ostream &operator<<(ostream &os, const Collection<T> &C) {
  for (size_t i = 0; i < C.size(); i++) {
    os << C[i];
  }
  return os;
}

} // namespace sdds

#endif // ! SDDS_COLLECTION_H

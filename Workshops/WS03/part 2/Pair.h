#ifndef SDDS_PAIR_H
#define SDDS_PAIR_H

#include <ostream>
namespace sdds {

template <typename V, class K> // a
class Pair {
public:
  Pair() = default;
  Pair(const K &key, const V &value);
  Pair(Pair &&) = default;
  Pair(const Pair &) = default;
  Pair &operator=(Pair &&) = default;
  Pair &operator=(const Pair &) = default;
  ~Pair() = default;

  const V &value() const { return _value; }
  const K &key() const { return _key; }
  virtual void display(std::ostream &os) const;

protected: // any other way other than protected?
  V _value;
  K _key;
};

template <typename V, class K> // a
Pair<V, K>::Pair(const K &key, const V &value) {
  _key = key;
  _value = value;
}

template <typename V, class K> // a
void Pair<V, K>::display(std::ostream &os) const {
  os << _key << " : " << _value << std::endl;
}

template <typename V, class K> // a
std::ostream &operator<<(std::ostream &os, const Pair<V, K> &pair) {
  pair.display(os);
  return os;
}

} // namespace sdds

#endif // !SDDS_PAIR_H

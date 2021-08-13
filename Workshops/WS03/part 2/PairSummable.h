#ifndef SDDS_PAIRSUMMABLE_H
#define SDDS_PAIRSUMMABLE_H
#include "Pair.h"
#include <iomanip>
#include <string>

namespace sdds {

template <typename V, class K> // a
class PairSummable : public Pair<V, K> {
public:
  PairSummable() : Pair<V, K>() {}
  PairSummable(const K &key, const V &value = _initial);
  PairSummable(PairSummable &&) = default;
  PairSummable(const PairSummable &) = default;
  PairSummable &operator=(PairSummable &&) = default;
  PairSummable &operator=(const PairSummable &) = default;
  ~PairSummable() = default;

  bool isCompatibleWith(const PairSummable<V, K> &b) const;
  PairSummable<V, K> &operator+=(const PairSummable<V, K> &pair);
  void display(std::ostream &os) const override;

private:
  static V _initial;
  static size_t _minWidth;
};

template <typename V, class K> // a
size_t PairSummable<V, K>::_minWidth = 0;

template <typename V, class K> // a
V PairSummable<V, K>::_initial{};

template <typename V, class K> // a
PairSummable<V, K>::PairSummable(const K &key, const V &value)
    : Pair<V, K>(key, value) {
  if (_minWidth < key.size()) {
    _minWidth = key.size();
  }
}

template <typename V, class K> // aaaaaaaaaaaaaaaaaaaaaaa
bool PairSummable<V, K>::isCompatibleWith(const PairSummable<V, K> &b) const {
  return this->key() == b.key();
}

template <typename V, class K> // aaaaaaaaaaaaaaaaaaaaaaa
PairSummable<V, K> &
PairSummable<V, K>::operator+=(const PairSummable<V, K> &pair) {
  this->_value += pair._value;
  return *this;
}

template <typename V, class K> // aaaaaaaaaaaaaaaaaaaaaaa
void PairSummable<V, K>::display(std::ostream &os) const {
  os << std::left << std::setw(_minWidth);
  Pair<V, K>::display(os);
  os << std::right;
}

template <> // aaaaaaaaaaaaaaaaaaaaaaa
PairSummable<std::string, std::string> &
PairSummable<std::string, std::string>::operator+=(
    const PairSummable<std::string, std::string> &pair) {

  if (this->_value.empty())
    this->_value = pair._value;
  else
    this->_value += ", " + pair._value;
  return *this;
}

} // namespace sdds

#endif // !SDDS_PAIRSUMMABLE_H

// Pair<int, student> X;

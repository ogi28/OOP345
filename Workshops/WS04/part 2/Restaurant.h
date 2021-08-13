#ifndef SDDS_RESTAURANT_H
#define SDDS_RESTAURANT_H

#include "Reservation.h"
namespace sdds {

class Restaurant {
public:
  Restaurant() {
    _res = nullptr;
    _resCount = 0;
  }
  Restaurant(const Reservation *reservations[], size_t cnt);

  Restaurant(Restaurant &&M) : Restaurant() { *this = std::move(M); }
  Restaurant(const Restaurant &C) : Restaurant() { *this = C; }
  Restaurant &operator=(Restaurant &&);
  Restaurant &operator=(const Restaurant &);
  ~Restaurant() { empty(); }

  size_t size() const { return _resCount; };

  friend ostream &operator<<(ostream &, const Restaurant &);

private:
  Reservation *_res;
  size_t _resCount;
  void empty() {
    if (_res) {
      delete[] _res;
      _res = nullptr;
    }
    _resCount = 0;
  }
};

Restaurant::Restaurant(const Reservation *reservations[], size_t cnt) {
  _resCount = cnt;
  _res = new Reservation[cnt];
  for (size_t i = 0; i < cnt; i++) {
    _res[i] = *reservations[i];
  }
}

Restaurant &Restaurant::operator=(Restaurant &&M) {

  if (this != &M) {
    empty();
    _resCount = M._resCount;
    _res = M._res;
    M._res = nullptr;
    M._resCount = 0;
  }
  return *this;
}
Restaurant &Restaurant::operator=(const Restaurant &C) {
  if (this != &C) {
    empty();
    _resCount = C._resCount;
    _res = new Reservation[_resCount];

    for (size_t i = 0; i < _resCount; i++) {
      _res[i] = C._res[i];
    }
  }

  return *this;
}

ostream &operator<<(ostream &os, const Restaurant &R) {
  using std::endl;
  static size_t CALL_CNT = 0;
  CALL_CNT++;

  os << "--------------------------\nFancy Restaurant (" << CALL_CNT << ')'
     << endl;
  os << "--------------------------" << endl;

  if (!R._resCount) // placeholder
  {
    os << "This restaurant is empty!\n";
  } else {
    for (size_t i = 0; i < R._resCount; i++) {
      os << R._res[i];
    }
  }
  os << "--------------------------" << endl;
  return os;
}

} // namespace sdds

#endif // !SDDS_RESTAURANT_H

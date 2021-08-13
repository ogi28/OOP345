#ifndef SDDS_CONFIRMATIONSENDER_H
#define SDDS_CONFIRMATIONSENDER_H

#include "Reservation.h"

namespace sdds {
class ConfirmationSender {
public:
  ConfirmationSender() {
    _capacity = 1;
    _res = (const Reservation **)new Reservation *[_capacity];
    _res[0] = nullptr;
    _resCount = 0;
  }
  ConfirmationSender(ConfirmationSender &&);
  ConfirmationSender(const ConfirmationSender &);
  ConfirmationSender &operator=(ConfirmationSender &&);
  ConfirmationSender &operator=(const ConfirmationSender &);
  ~ConfirmationSender();

  ConfirmationSender &operator+=(const Reservation &res);
  ConfirmationSender &operator-=(const Reservation &res);

  friend ostream &operator<<(ostream &, const ConfirmationSender &);

private:
  const Reservation **_res;
  size_t _resCount;
  size_t _capacity;
  int find(const Reservation &) const;
  void empty() {
    /* delete[] _res; */

    _res = nullptr;
    _resCount = 0;
    _capacity = 0;
  }
};

ConfirmationSender::ConfirmationSender(ConfirmationSender &&M) {
  *this = std::move(M);
}
ConfirmationSender::ConfirmationSender(const ConfirmationSender &C) {
  *this = C;
}
ConfirmationSender &ConfirmationSender::operator=(ConfirmationSender &&M) {
  if (this != &M) {
    empty();
    _capacity = M._capacity;
    _resCount = M._resCount;
    _res = M._res;
    M._resCount = 0;
    M._res = nullptr;
    M._capacity = 0;
  }

  return *this;
}
ConfirmationSender &ConfirmationSender::operator=(const ConfirmationSender &C) {
  if (this != &C) {
    empty();
    _capacity = C._capacity;
    _resCount = C._resCount;
    _res = (const Reservation **)new Reservation *[_capacity];

    for (size_t i = 0; i < _capacity; i++) {
      _res[i] = C._res[i];
    }
  }

  return *this;
}

ConfirmationSender::~ConfirmationSender() {
  delete[] _res;

  empty();
}

int ConfirmationSender::find(const Reservation &R) const {
  int retVal = -1;
  for (size_t i = 0; i < _capacity; ++i) {
    if (_res[i] == &R) {
      retVal = i;
    }
  }

  return retVal;
}

ConfirmationSender &ConfirmationSender::operator+=(const Reservation &res) {
  if (find(res) == -1) {
    int i = _capacity - 1;
    while (i >= 0 && _res[i] == nullptr) {
      i--;
    }
    if (static_cast<size_t>(i) == _capacity - 1) { // no empty slot at the end
      // expand
      const Reservation **temp =
          (const Reservation **)new Reservation *[_capacity * 2];
      for (size_t k = 0; k < _capacity * 2; k++) {
        temp[k] = nullptr;
      }
      for (size_t j = 0; j < _capacity; ++j) {
        temp[j] = _res[j];
      }
      _capacity *= 2;
      delete[] _res;
      _res = (const Reservation **)temp;
    }

    _res[i + 1] = &res;
    _resCount++;
  }

  return *this;
}
ConfirmationSender &ConfirmationSender::operator-=(const Reservation &res) {
  int i = find(res);
  if (i != -1) {
    _res[i] = nullptr;
    _resCount--;
    if (_resCount < _capacity / 2) {
      _capacity /= 2;
      const Reservation **temp =
          (const Reservation **)new Reservation *[_capacity];
      for (size_t i = 0; i < _capacity; i++) {
        temp[i] = nullptr;
      }
      for (size_t i = 0; i < _capacity * 2; i++) {
        if (_res[i]) {
          temp[i] = (const Reservation *)_res[i];
        }
      }
      delete[] _res;
      _res = temp;
    }
  }

  return *this;
}
ostream &operator<<(ostream &os, const ConfirmationSender &cs) {

  os << "--------------------------\nConfirmations to "
        "Send\n--------------------------\n";

  if (!cs._resCount) {
    os << "There are no confirmations to send!\n";
  } else {
    for (size_t i = 0; i < cs._capacity; i++) {
      if (cs._res[i]) {
        os << *cs._res[i];
      }
    }
  }

  os << "--------------------------\n";

  return os;
}
} // namespace sdds

#endif // !SDDS_CONFIRMATIONSENDER_H

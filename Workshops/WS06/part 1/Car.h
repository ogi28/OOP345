#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include "Vehicle.h"
//#include <fstream>
#include <iostream>
#include <string>

using std::istream;
using std::string;

namespace sdds {
class Car : public Vehicle {
public:
  Car() = default;
  Car(istream &in);
  Car(Car &&) = default;
  Car(const Car &) = default;
  Car &operator=(Car &&) = default;
  Car &operator=(const Car &) = default;
  ~Car() = default;

  string condition() const;
  double topSpeed() const;
  void display(std::ostream &out) const;

private:
  string _maker;
  double _maxSpeed;
  char _condition;
};

} // namespace sdds

#endif // !SDDS_CAR_H

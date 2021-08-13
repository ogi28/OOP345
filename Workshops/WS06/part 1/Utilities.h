#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include "Car.h"

namespace sdds {
Vehicle *createInstance(std::istream &in) {
  Vehicle *vehicle = nullptr;
  char read = ' ';
  while (in.get(read) && read == ' ')
    ;

  if (read == 'c' || read == 'C') {
    vehicle = new Car(in);
  }

  return vehicle;
}

} // namespace sdds

#endif // !SDDS_UTILITIES_H

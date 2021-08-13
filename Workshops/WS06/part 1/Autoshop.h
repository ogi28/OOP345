#ifndef SDDS_AUTOSHOP_H
#define SDDS_AUTOSHOP_H

#include "Vehicle.h"
#include <vector>
namespace sdds {
class Autoshop {
public:
  Autoshop() = default;
  Autoshop(Autoshop &&) = default;
  Autoshop(const Autoshop &) = default;
  Autoshop &operator=(Autoshop &&) = default;
  Autoshop &operator=(const Autoshop &) = default;
  ~Autoshop() = default;

  Autoshop &operator+=(Vehicle *theVehicle);
  void display(std::ostream &out) const;

private:
  std::vector<Vehicle *> m_vehicles;
};
} // namespace sdds

#endif // !SDDS_AUTOSHOP_H

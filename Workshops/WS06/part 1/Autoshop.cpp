#include "Autoshop.h"

namespace sdds {
Autoshop &Autoshop::operator+=(Vehicle *theVehicle) {
  m_vehicles.push_back(theVehicle);
  return *this;
}

void Autoshop::display(std::ostream &out) const {
  using std::vector;

  out << "--------------------------------\n";
  out << "| Cars in the autoshop!        |\n";
  out << "--------------------------------\n";

  for (vector<Vehicle *>::const_iterator i = m_vehicles.begin();
       i != m_vehicles.end(); i++) {
    /* (*i)->display(out); */
    (*(*i)).display(out);
    out << '\n';
  }

  out << "--------------------------------\n";
}

} // namespace sdds

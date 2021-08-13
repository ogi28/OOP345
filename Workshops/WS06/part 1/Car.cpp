#include "Car.h"
#include "utils.h"
#include <iomanip>

namespace sdds {

Car::Car(istream &in) {
  string word;
  in.ignore(1000, ',');
  getline(in, word, ',');
  _maker = trim(word);
  getline(in, word, ',');
  _condition = trim(word)[0];
  getline(in, word);
  _maxSpeed = stod(trim(word));

  /* std::stringstream */
}
string Car::condition() const {
  switch (_condition) {
  case 'u':
    return "used";
  case 'n':
    return "new";
  case 'b':
    return "broken";
  default:
    throw "Wrong condition";
  }
}
double Car::topSpeed() const { return _maxSpeed; }
void Car::display(std::ostream &out) const {
  using std::fixed;
  using std::left;
  using std::right;
  using std::setprecision;
  using std::setw;
  out << "| " << right << setw(10) << _maker << " | " << left << setw(6)
      << condition() << " | " << right << fixed << setprecision(2) << setw(6)
      << _maxSpeed << " |";
  /// n
}

} // namespace sdds

#include "Movie.h"
#include <iomanip>

namespace sdds {

Movie::Movie(const std::string &strMovie) {
  size_t pos1 = strMovie.find(',');
  _title = trim(strMovie.substr(0, pos1));

  size_t pos2 = strMovie.find(',', pos1 + 1);
  _year = stoi(trim(strMovie.substr(pos1 + 1, pos2 - pos1 - 1)));
  _desc = trim(strMovie.substr(pos2 + 1));
}

ostream &operator<<(ostream &os, const Movie &M) {
  using std::right;
  using std::setw;

  os << right << setw(40) << M._title << " | ";
  os << right << setw(4) << M._year << " | ";
  os << M._desc << std::endl;

  return os;
}
} // namespace sdds

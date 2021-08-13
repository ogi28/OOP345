#include "Book.h"
#include <iomanip>

namespace sdds {

Book::Book() {
  _year = 0;
  _price = 0.0;
}

Book::Book(const std::string &strBook) {
  size_t pos1 = strBook.find(',');

  _author = trim(strBook.substr(0, pos1));

  size_t pos2 = strBook.find(',', pos1 + 1);
  _title = trim(strBook.substr(pos1 + 1, pos2 - pos1 - 1));
  pos1 = strBook.find(',', pos2 + 1);
  _country = trim(strBook.substr(pos2 + 1, pos1 - pos2 - 1));
  pos2 = strBook.find(',', pos1 + 1);
  _price = stod(trim(strBook.substr(pos1 + 1, pos2 - pos1 - 1)));
  pos1 = strBook.find(',', pos2 + 1);
  _year = stoi(trim(strBook.substr(pos2 + 1, pos1 - pos2 - 1)));
  _desc = trim(strBook.substr(pos1 + 1));

  /* size_t pos2 = sd */
}

const std::string &Book::title() const { return _title; }
const std::string &Book::country() const { return _country; }
const size_t &Book::year() const { return _year; }
double &Book::price() { return _price; }

ostream &operator<<(ostream &os, const Book &B) {
  using std::right;
  using std::setw;

  os << right << setw(20) << B._author << " | ";
  os << right << setw(22) << B._title << " | ";
  os << right << setw(5) << B._country << " | ";
  os << right << setw(4) << B._year << " | ";
  os << right << setw(6) << std::fixed << std::setprecision(2) << B._price
     << " | ";
  os << B._desc << std::endl;

  return os;
}

} // namespace sdds

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include "utils.h"
#include <ostream>
using std::ostream;
namespace sdds

{
class Book {
public:
  Book();
  Book(const std::string &strBook);
  Book(Book &&) = default;
  Book(const Book &) = default;
  Book &operator=(Book &&) = default;
  Book &operator=(const Book &) = default;
  ~Book() = default;

  const std::string &title() const;
  const std::string &country() const;
  const size_t &year() const;
  double &price();

  template <class T> void fixSpelling(T &spellChecker) { spellChecker(_desc); }

  friend ostream &operator<<(ostream &, const Book &);

private:
  string _author;
  string _title;
  string _country;
  size_t _year;
  double _price;
  string _desc;
};

} // namespace sdds

#endif // !SDDS_BOOK_H

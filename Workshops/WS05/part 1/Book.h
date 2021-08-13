#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <ostream>
#include <string>
using std::ostream;
using std::string;
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

  friend ostream &operator<<(ostream &, const Book &);

private:
  string _author;
  string _title;
  string _country;
  size_t _year;
  double _price;
  string _desc;
  string trim(string str) {
    //  "     hello     world"
    int i = 0;
    size_t len = str.length();

    while (len > static_cast<size_t>(i) && str[i] == ' ')
      i++;
    if (i > 0)
      str.erase(0, i);

    len = str.length();
    i = len - 1;

    while (i >= 0 && str[i] == ' ') {
      i--;
    }

    if (static_cast<size_t>(i) < len - 1)
      str.erase(i + 1);

    return str;
  };
};

} // namespace sdds

#endif // !SDDS_BOOK_H

#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include "utils.h"
using std::ostream;
using std::string;

namespace sdds {
class Movie {
public:
  Movie() { _year = 0; }
  Movie(const std::string &strMovie);
  Movie(Movie &&) = default;
  Movie(const Movie &) = default;
  Movie &operator=(Movie &&) = default;
  Movie &operator=(const Movie &) = default;
  ~Movie() = default;

  const std::string &title() const { return _title; }

  template <class T> void fixSpelling(T &spellChecker) {
    spellChecker(_desc);
    spellChecker(_title);
  }

  friend ostream &operator<<(ostream &, const Movie &);

private:
  string _title;
  size_t _year;
  string _desc;
};

} // namespace sdds

#endif // !SDDS_MOVIE_H

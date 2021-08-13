#ifndef SDDS_RESERVATION_H
#define SDDS_RESERVATION_H

#include <iomanip>
#include <ostream>
#include <string>
using std::ostream;
using std::size_t;
using std::string;

namespace sdds {

class Reservation {
public:
  Reservation();
  Reservation(const string &res);
  Reservation(Reservation &&) = default;
  Reservation(const Reservation &) = default;
  Reservation &operator=(Reservation &&) = default;
  Reservation &operator=(const Reservation &) = default;
  ~Reservation() = default;

  friend ostream &operator<<(ostream &os, const Reservation &R);

private:
  string _resID;
  string _resName;
  string _resEmail;
  size_t _resDay;
  size_t _resHour;
  size_t _headCount;
  string &trim(string &str) {
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

// cpp
inline Reservation::Reservation() {
  _resDay = 0;
  _resHour = 0;
  _headCount = 0;
}

Reservation::Reservation(const string &res) {
  // 1234: John    ,  john@email.com  ,           2,   3,    5

  size_t pos1 = res.find(':'), pos2 = res.find(',');
  string sub = res.substr(0, pos1);
  _resID = trim(sub);

  sub = res.substr(pos1 + 1, pos2 - (pos1 + 1));
  _resName = trim(sub);

  pos1 = res.find(',', pos2 + 1);
  sub = res.substr(pos2 + 1, pos1 - (pos2 + 1));
  _resEmail = trim(sub);

  pos2 = res.find(',', pos1 + 1);
  sub = res.substr(pos1 + 1, pos2 - (pos1 + 1));
  _headCount = stoi(trim(sub));

  pos1 = res.find(',', pos2 + 1);
  sub = res.substr(pos2 + 1, pos1 - (pos2 + 1));
  _resDay = stoi(trim(sub));

  sub = res.substr(pos1 + 1);
  _resHour = stoi(trim(sub));

  // res.substr(, res.find(',');
  // substr
  // find
  // erase
  // stoi
}

ostream &operator<<(ostream &os, const Reservation &R) {

  using std::left;
  using std::right;
  using std::setw;

  os << "Reservation " << std::right << setw(10) << R._resID << ": " << right
     << setw(20) << R._resName << "  <" << left << setw(23)
     << R._resEmail + ">";

  if (R._resHour <= 9 && R._resHour >= 6) {
    os << "Breakfast";
  } else if (R._resHour <= 15 && R._resHour >= 11) {
    os << "Lunch";
  } else if (R._resHour <= 21 && R._resHour >= 17) {
    os << "Dinner";
  } else {
    os << "Drinks";
  }

  os << " on day " << R._resDay << " @ " << R._resHour << ":00 for "
     << R._headCount;
  if (R._headCount == 1)
    os << " person.\n";
  else {
    os << " people.\n";
  }

  return os;
}

} // namespace sdds

#endif // !SDDS_RESERVATION_H

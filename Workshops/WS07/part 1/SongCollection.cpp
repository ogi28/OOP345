#include "SongCollection.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::ifstream;
namespace sdds {

SongCollection::SongCollection(char *filename) {
  using std::getline;

  ifstream file(filename);
  if (!file.is_open()) {
    throw "Filename is incorrect";
  }
  string line;
  char str[26];
  string yearCheck;
  Song S;
  while (getline(file, line)) {
    std::stringstream ss(line);
    ss.get(str, 26);
    /* string temp(str); */
    S.title = trim(str);
    ss.get(str, 26);
    S.artist = trim(str);
    ss.get(str, 26);
    S.album = trim(str);
    ss.get(str, 6);
    yearCheck = trim(str);
    if (yearCheck.empty()) {
      S.year = 0;
    } else {
      S.year = stoi(yearCheck);
    }
    ss.get(str, 6);
    S.len = stoi(trim(str));
    ss.get(str, 6);
    S.price = stod(trim(str));
    collection.push_back(S);
  }
}

void SongCollection::display(ostream &out) const {
  auto print = [&out](const Song &S) -> void { out << S; };

  std::for_each(collection.begin(), collection.end(), print);
}

std::ostream &operator<<(std::ostream &out, const Song &theSong) {

  using std::fixed;
  using std::left;
  using std::right;
  using std::setprecision;
  using std::setw;
  using std::to_string;
  out << "| " << left << setw(20) << theSong.title << " | " << left << setw(15)
      << theSong.artist << " | " << left << setw(20) << theSong.album << " | "
      << right << setw(6) << (theSong.year != 0 ? to_string(theSong.year) : "")
      << " | " << getLen(theSong) << " | " << setprecision(2) << fixed
      << theSong.price << " |\n";

  return out;
}

string getLen(Song S) {
  using std::to_string;

  string ret = to_string(S.len / 60) + ":";
  size_t secs = S.len % 60;
  if (secs < 10) {
    ret += '0' + to_string(secs);
  } else {
    ret += to_string(secs);
  }

  return ret;
}

} // namespace sdds

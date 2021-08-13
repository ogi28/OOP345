#include "SongCollection.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
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
    S.m_title = trim(str);
    ss.get(str, 26);
    S.m_artist = trim(str);
    ss.get(str, 26);
    S.m_album = trim(str);
    ss.get(str, 6);
    yearCheck = trim(str);
    if (yearCheck.empty()) {
      S.m_year = 0;
    } else {
      S.m_year = stoi(yearCheck);
    }
    ss.get(str, 6);
    S.m_len = stoi(trim(str));
    ss.get(str, 6);
    S.m_price = stod(trim(str));
    collection.push_back(S);
  }
}

void SongCollection::display(ostream &out) const {
  using std::right;
  using std::setw;

  auto print = [&out](const Song &S) -> void { out << S; };
  std::for_each(collection.begin(), collection.end(), print);

  auto totalTime = [](size_t sum, const Song &S) -> size_t {
    sum += S.m_len;
    return sum;
  };
  size_t sum =
      std::accumulate(collection.begin(), collection.end(), 0, totalTime);

  out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
  out << "| " << setw(84) << right << "Total Listening Time: " + getLen(sum)
      << " |\n";
}

std::ostream &operator<<(std::ostream &out, const Song &theSong) {

  using std::fixed;
  using std::left;
  using std::right;
  using std::setprecision;
  using std::setw;
  using std::to_string;
  out << "| " << left << setw(20) << theSong.m_title << " | " << left
      << setw(15) << theSong.m_artist << " | " << left << setw(20)
      << theSong.m_album << " | " << right << setw(6)
      << (theSong.m_year != 0 ? to_string(theSong.m_year) : "") << " | "
      << getLen(theSong.m_len) << " | " << setprecision(2) << fixed
      << theSong.m_price << " |\n";

  return out;
}

string getLen(size_t length) {
  using std::to_string;
  string ret = "";
  int hours = length / 3600;
  if (hours > 0) {
    ret += to_string(hours) + ":";
  }

  length = length % 3600;
  int mins = length / 60;
  if (hours > 0 && mins < 10) {
    ret += '0' + to_string(mins) + ":";
  } else {
    ret += to_string(mins) + ":";
  }

  int secs = length % 60;
  if (secs < 10) {
    ret += '0' + to_string(secs);
  } else {
    ret += to_string(secs);
  }

  return ret;
}

void SongCollection::sort(string fieldName) {

  auto compare = [fieldName](const Song &S1, const Song &S2) -> int {
    int ret = 0;

    if (fieldName == "title") {
      ret = S1.m_title < S2.m_title;
    } else if (fieldName == "album") {
      ret = S1.m_album < S2.m_album;
    } else if (fieldName == "length") {
      ret = S1.m_len < S2.m_len;
    }

    return ret;
  };
  std::sort(collection.begin(), collection.end(), compare);
};

void SongCollection::cleanAlbum() {

  auto modify = [](Song S) -> Song {
    if (S.m_album == "[None]") {
      S.m_album = "";
    }
    return S;
  };

  std::transform(collection.begin(), collection.end(), collection.begin(),
                 modify);
}

bool SongCollection::inCollection(string artistName) const {
  auto pred = [artistName](const Song &S) -> bool {
    return S.m_artist == artistName;
  };
  return std::any_of(collection.begin(), collection.end(), pred);
}

std::list<Song> SongCollection::getSongsForArtist(string artistName) const {

  auto pred = [artistName](const Song &S) -> bool {
    return S.m_artist == artistName;
  };

  std::list<Song> filterList(collection.size());
  auto end = std::copy_if(collection.begin(), collection.end(),
                          filterList.begin(), pred);
  filterList.resize(
      std::distance(filterList.begin(), end)); // shrink container to new size

  return filterList;
};

} // namespace sdds

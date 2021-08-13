#ifndef SDDS_SONGCOLLECTION_H
#define SDDS_SONGCOLLECTION_H
#include <string>
#include <vector>
using std::ostream;
using std::string;
using std::vector;

namespace sdds {

struct Song {
  string artist;
  string title;
  string album;
  double price;
  size_t year;
  size_t len;
};

class SongCollection {
public:
  SongCollection();
  SongCollection(char *filename);
  SongCollection(SongCollection &&) = default;
  SongCollection(const SongCollection &) = default;
  SongCollection &operator=(SongCollection &&) = default;
  SongCollection &operator=(const SongCollection &) = default;
  ~SongCollection() = default;

  void display(ostream &out) const;

private:
  vector<Song> collection;
};
std::ostream &operator<<(std::ostream &out, const Song &theSong);
string getLen(Song S);

} // namespace sdds

#endif // !SDDS_SONGCOLLECTION_H

#ifndef SDDS_SONGCOLLECTION_H
#define SDDS_SONGCOLLECTION_H
#include <list>
#include <string>
#include <vector>
using std::ostream;
using std::string;
using std::vector;

namespace sdds {

struct Song {
  string m_artist;
  string m_title;
  string m_album;
  double m_price;
  size_t m_year;
  size_t m_len;
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
  void sort(string fieldName);
  void cleanAlbum();
  bool inCollection(string artistName) const;
  std::list<Song> getSongsForArtist(string artistName) const;

private:
  vector<Song> collection;
};
std::ostream &operator<<(std::ostream &out, const Song &theSong);
string getLen(size_t);

} // namespace sdds

#endif // !SDDS_SONGCOLLECTION_H

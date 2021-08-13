#ifndef SDDS_STRINGSET_H
#define SDDS_STRINGSET_H

#include <cstddef>
#include <string>
namespace sdds {
class StringSet {
public:
  StringSet();
  StringSet(char *filename);
  StringSet(StringSet &&) = default;
  StringSet(const StringSet &);
  StringSet &operator=(StringSet &&) = default;
  StringSet &operator=(const StringSet &);
  ~StringSet();

  size_t size() const;
  std::string operator[](size_t index) const;

private:
  std::string *_set;
  std::size_t _size;
  void empty() {
    if (_set) {
      delete[] _set;
      _set = nullptr;
    }
  }
};

} // namespace sdds
#endif // !SDDS_STRINGSET_H

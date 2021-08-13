#include "StringSet.h"
#include <cstddef>
#include <fstream>
#include <string>
namespace sdds {

StringSet::StringSet() { setDefault(); }

StringSet::StringSet(char *filename) : StringSet() {
  std::string word;
  size_t count = 0;
  std::ifstream file(filename);
  if (file.is_open()) {
    while (std::getline(file, word, ' ')) {
      count++;
    }
    file.clear();  // clear the error we get from reaching EOF
    file.seekg(0); // put the cursor at the beginning of file
    _set = new std::string[count];

    while (std::getline(file, word, ' ')) {
      _set[_size] = word;
      _size++;
    }
    file.close();
  }
}

StringSet::StringSet(const StringSet &C) : StringSet() { *this = C; }

StringSet &StringSet::operator=(const StringSet &C) {
  if (this != &C) {
    _size = C._size;
    empty();
    _set = new std::string[_size];
    for (size_t i = 0; i < _size; i++) {
      _set[i] = C._set[i];
    }
  }
  return *this;
}

StringSet::~StringSet() { empty(); }

StringSet::StringSet(StringSet &&M) : StringSet() {
  *this = std::move(M);
  //*this = M;
}

StringSet &StringSet::operator=(StringSet &&M) {
  if (this != &M) {
    empty();
    _size = M._size;
    _set = std::move(M._set);
    M.setDefault();
  }

  return *this;
}

size_t StringSet::size() const { return _size; }

std::string StringSet::operator[](size_t index) const {
  std::string str = "";
  if (index < _size) {
    str = _set[index];
  }

  return str;
}

} // namespace sdds

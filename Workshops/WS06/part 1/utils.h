#ifndef utils
#define utils
#include <string>
using std::string;

inline string trim(string str) {
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
}

#endif // !utils

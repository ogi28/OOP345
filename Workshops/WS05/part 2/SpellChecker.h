#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#include <fstream>
#include <iomanip>
#include <string>
using std::string;
#define MAX 6
namespace sdds {

class SpellChecker {
public:
  SpellChecker() = default;
  SpellChecker(const char *filename) {

    std::ifstream file(filename);
    if (!file.is_open()) {
      throw "Bad file name!";
    }
    size_t i = 0;
    string good, bad;
    while (file >> bad >> good) {
      m_badWords[i] = bad;
      m_goodWords[i] = good;
      i++;
    }
    file.close();
  }
  SpellChecker(SpellChecker &&) = default;
  SpellChecker(const SpellChecker &) = default;
  SpellChecker &operator=(SpellChecker &&) = default;
  SpellChecker &operator=(const SpellChecker &) = default;
  ~SpellChecker() = default;

  void operator()(std::string &text) {
    size_t n = 0;

    for (size_t i = 0; i < MAX; i++) {
      while ((n = text.find(m_badWords[i])) != string::npos) {
        text.replace(n, m_badWords[i].length(), m_goodWords[i]);
        count[i]++;
      }
    }

  } // functor
  void showStatistics(std::ostream &out) const {
    using std::right;
    using std::setw;
    out << "Spellchecker Statistics\n";
    for (size_t i = 0; i < MAX; i++) {

      out << right << setw(15) << m_badWords[i] << ": " << count[i]
          << " replacements\n";
    }
  }

private:
  string m_badWords[MAX];
  string m_goodWords[MAX];
  size_t count[MAX]{};
};

} // namespace sdds

#endif // !SDDS_SPELLCHECKER_H

#include "event.h"
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

size_t g_sysClock /*  = 0*/;

namespace sdds {
void Event::setEmpty() {
  m_desc[0] = '\0';
  m_startTime = 0;
}

Event::Event() { setEmpty(); }

void Event::display() {
  static size_t counter = 0;
  counter++;
  size_t hour = m_startTime / 3600;
  size_t minutes = (m_startTime % 3600) / 60;
  size_t seconds = (m_startTime % 3600) % 60;

  cout << setw(2) << setfill(' ') << counter << ". ";
  if (m_desc[0]) {
    cout << setw(2) << setfill('0') << hour << ':' << setw(2) << setfill('0')
         << minutes << ':' << setw(2) << setfill('0') << seconds << " => "
         << m_desc << endl;
  } else
    cout << "| No Event |" << endl;
}

void Event::set(char *str) {
  if (str && str[0]) {
    strcpy(m_desc, str);
    m_startTime = g_sysClock;
  } else {
    setEmpty();
  }
}

} // namespace sdds

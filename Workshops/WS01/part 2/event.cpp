#include "event.h"
#include <cstring>
#include <iomanip>
#include <iostream>

/* using std::cout; */
/* using std::endl; */
using namespace std;

size_t g_sysClock /*  = 0*/;

namespace sdds {
void Event::setEmpty() {
  m_desc = nullptr;
  m_startTime = 0;
}
void Event::reset() {
  if (m_desc) {
    delete[] m_desc;
    m_desc = nullptr;
  }
}

Event::Event() { setEmpty(); }

Event::Event(const Event &C) : Event() { *this = C; }

Event &Event::operator=(const Event &C) {

  if (this != &C && C.m_desc && C.m_desc[0]) {
    reset();
    this->m_startTime = C.m_startTime;
    m_desc = new char[strlen(C.m_desc) + 1];
    strcpy(m_desc, C.m_desc);
  }

  return *this;
}

Event::~Event() {
  reset();
  m_startTime = 0;
}

void Event::display() {
  static size_t counter = 0;
  counter++;
  unsigned hour = m_startTime / 3600;
  unsigned minutes = (m_startTime % 3600) / 60;
  unsigned seconds = (m_startTime % 3600) % 60;

  cout << setw(2) << setfill(' ') << counter << ". ";
  if (m_desc && m_desc[0]) {
    cout << setw(2) << setfill('0') << hour << ':' << setw(2) << setfill('0')
         << minutes << ':' << setw(2) << setfill('0') << seconds << " => "
         << m_desc << endl;
  } else
    cout << "| No Event |" << endl;
}

void Event::set(char *str) {
  reset();
  if (str && str[0]) {
    m_desc = new char[strlen(str) + 1];
    strcpy(m_desc, str);
    m_startTime = g_sysClock;
  } else {
    setEmpty();
  }
}

} // namespace sdds

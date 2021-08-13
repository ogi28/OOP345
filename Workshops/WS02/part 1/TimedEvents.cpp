#include "TimedEvents.h"
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

namespace sdds {
TimedEvents::TimedEvents() { _noRecords = 0; }

void TimedEvents::startClock() {
  _startTime = std::chrono::steady_clock::now();
}

void TimedEvents::stopClock() { _endTime = std::chrono::steady_clock::now(); }

void TimedEvents::addEvent(const char *eventName) {
  events[_noRecords].name = new char[strlen(eventName) + 1];
  strcpy(events[_noRecords].name, eventName);

  events[_noRecords].unitOfTime = new char[12];
  strcpy(events[_noRecords].unitOfTime, "nanoseconds");

  events[_noRecords].duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          _endTime - _startTime); // c++ casting static/dynamic casting

  ++_noRecords;
}

std::ostream &operator<<(std::ostream &os, const TimedEvents &T) {

  os << "--------------------------\n";
  os << "Execution Times:\n";
  os << "--------------------------\n";
  for (size_t i = 0; i < T._noRecords; i++) {
    os << setw(21) << left << T.events[i].name << setw(13) << right
       << T.events[i].duration.count() << ' ' << T.events[i].unitOfTime << endl;
  }
  os << "--------------------------\n";

  return os;
}
} // namespace sdds

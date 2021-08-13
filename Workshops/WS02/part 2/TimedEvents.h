#ifndef SDDS_TIMEDEVENT_H
#define SDDS_TIMEDEVENT_H
#include <chrono>
#include <string>
namespace sdds {

struct Event {

  char *name;
  char *unitOfTime;
  std::chrono::steady_clock::duration
      duration; // https://en.cppreference.com/w/cpp/chrono/time_point

  Event() {
    name = nullptr;
    unitOfTime = nullptr;
  }
  ~Event() {
    if (name) {
      delete[] name;
      name = nullptr;
    }
    if (unitOfTime) {
      delete[] unitOfTime;
      name = unitOfTime;
    }
  }
};

class TimedEvents {
public:
  TimedEvents();
  TimedEvents(TimedEvents &&) = default;
  TimedEvents(const TimedEvents &) = default;
  TimedEvents &operator=(TimedEvents &&) = default;
  TimedEvents &operator=(const TimedEvents &) = default;
  ~TimedEvents() = default;

  void startClock();
  void stopClock();
  void addEvent(const char *);

  friend std::ostream &operator<<(std::ostream &, const TimedEvents &);

private:
  size_t _noRecords;
  std::chrono::steady_clock::time_point _startTime;
  std::chrono::steady_clock::time_point _endTime;
  Event events[10];
};

} // namespace sdds

#endif // !SDDS_TIMEDEVENT_H

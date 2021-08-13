#ifndef SDDS_EVENT_H
#define SDDS_EVENT_H

#include <cstddef>
extern size_t g_sysClock;

namespace sdds {
class Event {
public:
  Event();
  Event(Event &&) = default;
  Event(const Event &) = default;
  Event &operator=(Event &&) = default;
  Event &operator=(const Event &) = default;
  ~Event() = default;

  void display();
  void set(char *str = nullptr);

private:
  char m_desc[128];
  size_t m_startTime;
  void setEmpty();
};

} // namespace sdds

#endif // !SDDS_EVENT_H

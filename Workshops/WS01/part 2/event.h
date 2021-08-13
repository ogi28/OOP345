#ifndef SDDS_EVENT_H
#define SDDS_EVENT_H

#include <cstddef>
extern size_t g_sysClock;

namespace sdds {
class Event {
public:
  Event();
  Event(Event &&) = default;
  Event(const Event &);
  Event &operator=(Event &&) = default;
  Event &operator=(const Event &);
  ~Event();

  void display();
  void set(char *str = nullptr);

private:
  char *m_desc;
  size_t m_startTime;
  void setEmpty();
  void reset();
};

} // namespace sdds

#endif // !SDDS_EVENT_H

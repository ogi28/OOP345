#ifndef SDDS_SETSUMMABLE_H
#define SDDS_SETSUMMABLE_H
#include "Set.h"
#include <string>
namespace sdds {

template <size_t N, class T> // aaaaaaaaaaaaaaaaaaaaaaaaa
class SetSummable : public Set<N, T> {
public:
  SetSummable() : Set<N, T>() {}
  SetSummable(SetSummable &&) = default;
  SetSummable(const SetSummable &) = default;
  SetSummable &operator=(SetSummable &&) = default;
  SetSummable &operator=(const SetSummable &) = default;
  ~SetSummable() = default;

  T accumulate(const std::string &filter) const;
};

template <size_t N, class T> // aaaaaaaaaaaaaaaaaaaaaaaaa
T SetSummable<N, T>::accumulate(const std::string &filter) const {
  T accumulator(filter);

  for (size_t i = 0; i < this->size(); i++) {
    if (accumulator.isCompatibleWith(this->get(i))) {
      accumulator += this->get(i);
    }
  }
  return accumulator;
}

} // namespace sdds
#endif // !SDDS_SETSUMMABLE_H

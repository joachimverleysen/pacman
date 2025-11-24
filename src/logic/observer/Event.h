#include "Observer.h"
#ifndef Event

class Event {

public:
  virtual void apply(Observer &observer) {};
};

class CoinEatenEvent : public Event {};

class FruitEatenEvent : public Event {};

class GhostEatenEvent: public Event {};

class FrightenGhostsEvent: public Event {};

#endif // !Event

#ifndef PACMAN_EVENT_H
#define PACMAN_EVENT_H

#include "../observer/Observer.h"
class Visitor;

class Event {

public:
  virtual ~Event() = default;

  virtual void accept(Visitor &visitor) = 0;
};

class CoinEatenEvent : public Event {
public:
  void accept(Visitor &visitor) override;
};

class FruitEatenEvent : public Event {
public:
  void accept(Visitor &visitor) override;
};

class GhostEatenEvent: public Event {
public:
  void accept(Visitor &visitor) override;
};

class FrightenGhostsEvent: public Event {
public:
  void accept(Visitor &visitor) override;
};

class PacmanDiesEvent: public Event {
public:
  void accept(Visitor &visitor) override;
};

#endif // !PACMAN_EVENT_H

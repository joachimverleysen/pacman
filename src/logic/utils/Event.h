#ifndef PACMAN_EVENT_H
#define PACMAN_EVENT_H

#include "../observer/Observer.h"
class AbstractDispatcher;
class Visitor;

class Event {

public:
  virtual ~Event() = default;

  virtual void accept(Visitor &visitor) = 0;

  virtual void accept(AbstractDispatcher &dispatcher) = 0;
};

class CoinEatenEvent : public Event {
public:
  void accept(Visitor &visitor) override;
  void accept(AbstractDispatcher &dispatcher) override;
};

class FruitEatenEvent : public Event {
public:
  void accept(AbstractDispatcher &dispatcher) override;

  void accept(Visitor &visitor) override;
};

class GhostEatenEvent: public Event {
public:
  void accept(AbstractDispatcher &dispatcher) override;

  void accept(Visitor &visitor) override;
};

class FrightenGhostsEvent: public Event {
public:
  void accept(Visitor &visitor) override;

  void accept(AbstractDispatcher &dispatcher) override;
};

class PacmanDiesEvent: public Event {
public:
  void accept(AbstractDispatcher &dispatcher) override;

  void accept(Visitor &visitor) override;
};

class NewLevelEvent: public Event {
public:
  void accept(AbstractDispatcher &dispatcher) override;

  void accept(Visitor &visitor) override;
};

#endif // !PACMAN_EVENT_H

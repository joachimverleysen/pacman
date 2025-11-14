#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include "entity/AbstractFactory.h"
class State : public Subject {
protected:
  bool active_{true};
  std::unique_ptr<AbstractFactory> factory_;
public:
  State(std::unique_ptr<AbstractFactory> factory);
  virtual void initialize() = 0;
  virtual void update() = 0;
  virtual void handleAction(Action action) = 0;
  void close() {active_ = false;}
  bool closed() const {return !active_;}
};
#endif // PACMAN_STATE_H

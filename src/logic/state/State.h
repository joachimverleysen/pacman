#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include "../entity/AbstractFactory.h"

class AbstractDispatcher;
using namespace Utils;
class State {
public:
  virtual ~State() = default;

protected:
  std::vector<std::shared_ptr<Entity>> entities_;
  bool active_{true};
  std::shared_ptr<AbstractFactory> factory_;
  std::shared_ptr<AbstractDispatcher> dispatcher_;
public:
  State(std::shared_ptr<AbstractFactory> factory,
      std::shared_ptr<AbstractDispatcher> dispatcher);
  State(std::shared_ptr<AbstractFactory> factory);

  virtual void initialize() = 0;
  virtual void update() = 0;
  [[nodiscard]] virtual StateNS::Type getType() const = 0;
  virtual void handleAction(GameAction action) = 0;
  void close() {active_ = false;}
  bool closed() const {return !active_;}
};
#endif // PACMAN_STATE_H

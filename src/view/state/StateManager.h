#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include <stack>
#include <memory>

class StateView;
class State;
class EntityFactory;

class StateManager {

  std::stack<std::shared_ptr<StateView>> state_views_;
  std::shared_ptr<EntityFactory> factory_;

public:
  explicit StateManager(std::shared_ptr<EntityFactory> factory);

  [[nodiscard]] std::shared_ptr<StateView> getCurrentStateView() const;
  void updateCurrentState();

  void pushState(const std::shared_ptr<State>& state);

  bool empty() const;

  std::shared_ptr<State> getCurrentState() const;

  StateManager();

  void setFactory(const std::shared_ptr<EntityFactory> &factory);
};


#endif //PACMAN_STATEMANAGER_H

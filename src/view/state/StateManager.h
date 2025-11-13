#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include <stack>
#include <memory>

class StateView;
class State;

class StateManager {
  std::stack<std::shared_ptr<StateView>> state_views_;

public:
  std::shared_ptr<StateView> getCurrentStateView() const;
  void updateCurrentState();

  void pushState(const std::shared_ptr<State>& state);

};

#endif //PACMAN_STATEMANAGER_H

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include <stack>
#include <memory>
 #include "../../logic/utils/Utils.h"

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

  Utils::StateNS::Type getCurrentType() const;

  std::shared_ptr<EntityFactory> getFactory() const;

  void popCurrentState();

  void onLevelGameOver();

  void pushGameOverState();

  void loadNewLevel(std::shared_ptr<StateManager> ptr_to_this);

  void pushStartMenu(std::shared_ptr<StateManager> ptr_to_this);
};


#endif //PACMAN_STATEMANAGER_H

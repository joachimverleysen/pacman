#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include <stack>
#include <memory>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <map>
#include "../../logic/utils/Utils.h"

class StateView;
class State;
class EntityFactory;

using Action = std::function<void()>;
using EventMap = std::map<sf::Keyboard::Key, Action>;
using namespace Utils;

class StateManager {

  std::stack<std::shared_ptr<StateView>> state_views_;
  std::shared_ptr<EntityFactory> factory_;
  std::map<StateNS::Type, EventMap> fsm;
  std::weak_ptr<StateManager> ptr_to_this_;

  int difficulty_ = 1;

public:
  StateManager();

  explicit StateManager(std::shared_ptr<EntityFactory> factory);

  [[nodiscard]] std::shared_ptr<StateView> getCurrentStateView() const;
  void updateCurrentState();

  void pushState(const std::shared_ptr<State>& state);

  bool empty() const;

  std::shared_ptr<State> getCurrentState() const;


  void setPtrToThis(const std::weak_ptr<StateManager> &ptrToThis);

  void setFactory(const std::shared_ptr<EntityFactory> &factory);

  Utils::StateNS::Type getCurrentType() const;

  std::shared_ptr<EntityFactory> getFactory() const;

  void popCurrentState();

  void onGameOver();

  void pushGameOverState();

  void loadNewLevel(const std::weak_ptr<StateManager> &ptr_to_this);

  void pushStartMenu(std::shared_ptr<StateManager> ptr_to_this);

  void pushPauseState();

  void initialize();

  Action getAction(sf::Keyboard::Key key) const;

  void pushVictoryState();

  void onVictory();
};


#endif //PACMAN_STATEMANAGER_H

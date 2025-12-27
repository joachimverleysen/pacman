#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include "../../logic/utils/Utils.h"
#include <SFML/Window/Event.hpp>
#include <functional>
#include <map>
#include <memory>
#include <stack>

class Dispatcher;
class StateView;
class State;
class EntityFactory;

using Action = std::function<void()>;
using EventMap = std::map<sf::Keyboard::Key, Action>;
using namespace Utils;

// todo single resp
// todo more documentation
class StateManager {

  std::stack<std::shared_ptr<StateView>> state_views_;
  std::shared_ptr<EntityFactory> factory_;
  std::shared_ptr<AbstractDispatcher> dispatcher_;
  std::map<StateNS::Type, EventMap> fsm;
  std::weak_ptr<StateManager> ptr_to_this_;

  unsigned int difficulty_ = 1;
  unsigned int lives_remaining_ = 3;

public:
  StateManager();

  explicit StateManager(std::shared_ptr<EntityFactory> factory);

  /// Returns current state view
  [[nodiscard]] std::shared_ptr<StateView> getCurrentStateView() const;

  /// Calls update on current state
  void updateCurrentState();

  /// Pushes a state on the stack
  void pushState(const std::shared_ptr<State> &state);

  /// True if stack is empty
  bool empty() const;

  /// Returns pointer to current state
  std::shared_ptr<State> getCurrentState() const;

  /// Workaround to get a weak pointer to <this>
  void setPtrToThis(const std::weak_ptr<StateManager> &ptrToThis);

  /// Sets the entity factory
  void setFactory(const std::shared_ptr<EntityFactory> &factory);

  /// Sets the dispatcher
  void setDispatcher(const std::shared_ptr<AbstractDispatcher> &dispatcher);

  /// Returns type of current state
  Utils::StateNS::Type getCurrentType() const;

  /// Returns pointer to factory
  std::shared_ptr<EntityFactory> getFactory() const;

  /// Pops current state from stack
  void popCurrentState();

  /// on game over
  void onGameOver();

  /// pushes game over state
  void pushGameOverState();

  /// Loads new level
  void loadNewLevel(const std::weak_ptr<StateManager> &ptr_to_this);

  /// Pushes start menu
  void pushStartMenu(std::shared_ptr<StateManager> ptr_to_this);

  /// Pushes pause state
  void pushPauseState();

  /// Initializes
  void initialize();

  /// Converts a key (user input) to an action
  Action getAction(sf::Keyboard::Key key) const;

  /// Pushes victory state
  void pushVictoryState();

  /// on victory
  void onVictory();

  /// on pacman death
  void onPacmanDeath();
};

#endif // PACMAN_STATEMANAGER_H

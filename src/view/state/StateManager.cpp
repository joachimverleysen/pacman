#include "StateManager.h"

#include <utility>
#include "StateView.h"
#include "../EntityFactory.h"
#include "../../logic/state/GameOverState.h"
#include "../../logic/World.h"
#include "../../logic/state/MenuState.h"
#include "../../logic/state/PauseState.h"
#include "../../logic/state/VictoryState.h"

void StateManager::initialize() {
  if (ptr_to_this_.lock() == nullptr) {
    throw std::runtime_error("State manager in invalid state");
  }
  fsm[StateNS::Type::WORLD][sf::Keyboard::Space] = [this]() {pushPauseState();};
  fsm[StateNS::Type::PAUSE][sf::Keyboard::Space] = [this]() {popCurrentState();};
  fsm[StateNS::Type::PAUSE][sf::Keyboard::Q] = [this]() {
    popCurrentState();  // now at World
    popCurrentState();  // now at start menu
  };
  fsm[StateNS::Type::STARTMENU][sf::Keyboard::S] = [this]() { loadNewLevel(ptr_to_this_);};
  fsm[StateNS::Type::STARTMENU][sf::Keyboard::X] = [this]() {popCurrentState();};  // Will close game
  fsm[StateNS::Type::GAME_OVER][sf::Keyboard::Q] = [this]() {
    popCurrentState();
    difficulty_ = 1;
  };
  fsm[StateNS::Type::VICTORY][sf::Keyboard::Space] = [this]() {
    popCurrentState();
    loadNewLevel(ptr_to_this_);
  };

  fsm[StateNS::Type::VICTORY][sf::Keyboard::Q] = [this]() {
    popCurrentState();
    difficulty_ = 1;
  };
}

Action StateManager::getAction(sf::Keyboard::Key key) const {
    auto current_state_type = getCurrentState()->getType();

    auto it = fsm.find(current_state_type);
    if (it != fsm.end()) {
        auto& event_map = it->second;

        auto actionIt = event_map.find(key);
        if (actionIt != event_map.end()) {
            return actionIt->second;
        }
    }

    return [](){};
}


std::shared_ptr<StateView> StateManager::getCurrentStateView() const {
  return state_views_.top();
}

std::shared_ptr<State> StateManager::getCurrentState() const {
  return state_views_.top()->getState();
}

void StateManager::pushPauseState() {
  auto state = std::make_shared<PauseState>(factory_);
  pushState(state);
}

void StateManager::updateCurrentState() {
  if (empty())
    throw std::runtime_error("Can't update since state stack is empty");
  std::shared_ptr<StateView> current = state_views_.top();
  current->updateState();
  if (current->getState()->closed())
    state_views_.pop();
}

void StateManager::loadNewLevel(const std::weak_ptr<StateManager> &ptr_to_this) {
  std::shared_ptr<World> world = std::make_shared<World>(factory_, dispatcher_, ptr_to_this, difficulty_, lives_remaining_);
  pushState(world);
  difficulty_++;
}

void StateManager::pushStartMenu(std::shared_ptr<StateManager> ptr_to_this) {
  std::shared_ptr<MenuState> startmenu = std::make_shared<MenuState>(factory_, ptr_to_this);
  pushState(startmenu);
}
void StateManager::onGameOver() {
 state_views_.pop();
 pushGameOverState();
 difficulty_ = 1;
  lives_remaining_ = 3;
 Score::getInstance()->reset();
}

void StateManager::onVictory() {
  state_views_.pop();
  pushVictoryState();
}

void StateManager::onPacmanDeath() {
}

void StateManager::pushGameOverState() {
  std::shared_ptr<GameOverState> state = std::make_shared<GameOverState>(factory_);
  std::shared_ptr<StateView> view = std::make_shared<StateView>(state);
  state_views_.push(view);
  getCurrentState()->initialize();
}

void StateManager::pushVictoryState() {
  std::shared_ptr<VictoryState> state = std::make_shared<VictoryState>(factory_);
  std::shared_ptr<StateView> view = std::make_shared<StateView>(state);
  state_views_.push(view);
  getCurrentState()->initialize();
}

void StateManager::pushState(const std::shared_ptr<State>& state) {
  std::shared_ptr<StateView> view = std::make_shared<StateView>(state);
  state_views_.push(view);
  view->getState()->initialize();
}

bool StateManager::empty() const {
  return state_views_.empty();
}


StateManager::StateManager() {

}

void StateManager::setFactory(const std::shared_ptr<EntityFactory> &factory) {
  factory_ = factory;
}

void StateManager::setDispatcher(const std::shared_ptr<AbstractDispatcher> &dispatcher) {
  dispatcher_ = dispatcher;
}

std::shared_ptr<EntityFactory> StateManager::getFactory() const {
  return factory_;
}

StateNS::Type StateManager::getCurrentType() const {
  return getCurrentState()->getType();
}

void StateManager::popCurrentState() {
  state_views_.pop();
}

void StateManager::setPtrToThis(const std::weak_ptr<StateManager> &ptrToThis) {
  ptr_to_this_ = ptrToThis;
}


#include "StateManager.h"

#include <utility>
#include "StateView.h"
#include "../EntityFactory.h"
#include "../../logic/GameOverScreen.h"
#include "../../logic/World.h"
#include "../../logic/StartMenu.h"


std::shared_ptr<StateView> StateManager::getCurrentStateView() const {
  return state_views_.top();
}

std::shared_ptr<State> StateManager::getCurrentState() const {
  return state_views_.top()->getState();
}

void StateManager::updateCurrentState() {
  std::shared_ptr<StateView> current = state_views_.top();
  current->updateState();
  if (current->getState()->closed())
    state_views_.pop();
}

void StateManager::loadNewLevel(std::shared_ptr<StateManager> ptr_to_this) {
  std::shared_ptr<World> world = std::make_shared<World>(factory_, ptr_to_this);
  pushState(world);
}

void StateManager::pushStartMenu(std::shared_ptr<StateManager> ptr_to_this) {
  std::shared_ptr<StartMenu> startmenu = std::make_shared<StartMenu>(factory_, ptr_to_this);
  pushState(startmenu);
}
void StateManager::onLevelGameOver() {
 state_views_.pop();
 pushGameOverState();
}

void StateManager::pushGameOverState() {
  std::shared_ptr<GameOverScreen> state = std::make_shared<GameOverScreen>(factory_);
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

StateManager::StateManager(std::shared_ptr<EntityFactory> factory)
: factory_(std::move(factory)){

}

StateManager::StateManager() {

}

void StateManager::setFactory(const std::shared_ptr<EntityFactory> &factory) {
  factory_ = factory;
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


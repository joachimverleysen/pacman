#include "StateManager.h"
#include "StateView.h"


std::shared_ptr<StateView> StateManager::getCurrentStateView() const {
  return state_views_.top();
}

void StateManager::updateCurrentState() {
  std::shared_ptr<StateView> current = state_views_.top();
  current->updateState();
}

void StateManager::pushState(const std::shared_ptr<State>& state) {
  std::shared_ptr<StateView> view = std::make_shared<StateView>(state);
  state_views_.push(view);
}


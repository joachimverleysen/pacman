#include "StateView.h"

void StateView::updateState() {
  state_->update();
}

std::shared_ptr<State> StateView::getState() const {
  return state_;
}

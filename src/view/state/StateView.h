#ifndef PACMAN_STATEVIEW_H
#define PACMAN_STATEVIEW_H

#include "../../logic/State.h"
#include <memory>

class EntityView;
class Renderer;
class EntityFactory;
//
class StateView {
  std::shared_ptr<State> state_;
  std::vector<std::weak_ptr<EntityView>> views_;
public:
  friend Renderer;
  friend EntityFactory;
  StateView(std::shared_ptr<State> state) : state_(state) {};
  void updateState();
};
#endif //PACMAN_STATEVIEW_H

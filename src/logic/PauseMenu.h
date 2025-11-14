#ifndef PACMAN_PAUSEMENU_H
#define PACMAN_PAUSEMENU_H

#include <utility>
#include "utils/Utils.h"
#include "State.h"

class PauseMenu : public State {
public:
  PauseMenu(std::shared_ptr<AbstractFactory> factory)
  : State(factory) {};
  void initialize() override {}
  void update() override {}
  void handleAction(Action action) override {}
  [[nodiscard]] StateNS::Type getType() const override {return StateNS::Type::PAUSE;}
};


#endif //PACMAN_PAUSEMENU_H

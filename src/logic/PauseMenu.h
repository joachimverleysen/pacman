#ifndef PACMAN_PAUSEMENU_H
#define PACMAN_PAUSEMENU_H

#include "State.h"

class PauseMenu : public State {
public:
  void initialize() override {}
  void update() override {}
  void handleAction(Action action) override {}
};

#endif //PACMAN_PAUSEMENU_H

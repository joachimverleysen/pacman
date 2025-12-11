#ifndef PACMAN_GAMEOVERSCREEN_H
#define PACMAN_GAMEOVERSCREEN_H

#include "State.h"
#include "../utils/Utils.h"
#include <utility>


typedef std::shared_ptr<Entity> EntityPtr;

class GameOverState : public State {
  std::vector<EntityPtr> entities_;

public:
  GameOverState(std::shared_ptr<AbstractFactory> factory) : State(factory) {};
  void initialize() override;
  void update() override;
  void handleAction(GameAction action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::GAME_OVER;
  }
};

inline void GameOverState::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_GAMEOVERSCREEN_H

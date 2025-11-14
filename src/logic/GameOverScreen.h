#ifndef PACMAN_GAMEOVERSCREEN_H
#define PACMAN_GAMEOVERSCREEN_H

#include "State.h"
#include "utils/Utils.h"
#include <utility>

typedef std::shared_ptr<Entity> EntityPtr;

class GameOverScreen : public State {
  std::vector<EntityPtr> entities_;

public:
  GameOverScreen(std::shared_ptr<AbstractFactory> factory) : State(factory) {};
  void initialize() override;
  void update() override;
  void handleAction(GameAction action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::GAME_OVER;
  }
};

inline void GameOverScreen::initialize() {
  TextConfig config;
  // Title
  config.text = "Game Over";
  config.font = MyFont::PACFONT;
  config.character_size = 70;
  auto text_ = factory_->createText({0, 0}, config);
  entities_.push_back(text_);

  // Subtext
  TextConfig sconfig;
  sconfig.text = "Press Q to go to Start Menu";
  sconfig.font = MyFont::LIBER;
  text_ = factory_->createText({0, -0.4}, sconfig);
  entities_.push_back(text_);
}

inline void GameOverScreen::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_GAMEOVERSCREEN_H

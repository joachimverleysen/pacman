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
  void handleAction(Action action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::GAME_OVER;
  }
  void makeTitle();
};

void GameOverScreen::initialize() {
  std::string text, font;
  // Title
  text = "Game Over";
  font = "assets/font/Pacfont.ttf";
  auto text_ = factory_->createText({0, 0}, text, font, 70);
  entities_.push_back(text_);

  // Subtext
  text = "Press Q to go to Start Menu";
  font = "assets/font/liber.ttf";
  text_ = factory_->createText({0, -0.4}, text, font, 30);
  entities_.push_back(text_);
}

void GameOverScreen::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_GAMEOVERSCREEN_H

#ifndef PACMAN_PAUSEMENU_H
#define PACMAN_PAUSEMENU_H

#include "State.h"
#include "utils/Utils.h"
#include <utility>

typedef std::shared_ptr<Entity> EntityPtr;
class PauseMenu : public State {
  std::vector<EntityPtr> entities_;

public:
  PauseMenu(std::shared_ptr<AbstractFactory> factory) : State(factory) {};
  void initialize() override;
  void update() override;
  void handleAction(Action action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::PAUSE;
  }
  std::string getTitlePrompt() const;
};

std::string PauseMenu::getTitlePrompt() const { return "Pause Menu"; }

void PauseMenu::initialize() {

  std::string text, font;
  // Title
  text = "Pause Menu";
  font = "assets/font/Pacfont.ttf";
  auto text_ = factory_->createText({0, 0}, text, font, 70);
  entities_.push_back(text_);

  // Subtext
  text = "Press SPACE to continue";
  font = "assets/font/liber.ttf";
  text_ = factory_->createText({0, -0.4}, text, font, 30);
  entities_.push_back(text_);
}

void PauseMenu::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_PAUSEMENU_H

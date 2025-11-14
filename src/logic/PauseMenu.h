#ifndef PACMAN_PAUSEMENU_H
#define PACMAN_PAUSEMENU_H

#include <utility>
#include "utils/Utils.h"
#include "State.h"

typedef std::shared_ptr<Entity> EntityPtr;
class PauseMenu : public State {
  std::vector<EntityPtr> entities_;
public:
  PauseMenu(std::shared_ptr<AbstractFactory> factory)
  : State(factory) {};
  void initialize() override;
  void update() override;
  void handleAction(Action action) override {}
  [[nodiscard]] StateNS::Type getType() const override {return StateNS::Type::PAUSE;}
  std::string getTitlePrompt() const;

  void makeTitle();
};

std::string PauseMenu::getTitlePrompt() const {
  return "Pause Menu";
}

void PauseMenu::initialize() {
  makeTitle();

  // Subtext
  std::string text = "Press SPACE to continue";
  std::string font = "assets/arialfont/arial.ttf";
  auto text_ = factory_->createText({0, -0.4}, text, font, 30);
  entities_.push_back(text_);
}

void PauseMenu::makeTitle() {
  std::string title = "Pause Menu";
  std::string font = "assets/pacfont/Pacfont.ttf";
  auto text = factory_->createText({0, 0}, title, font, 70);
  entities_.push_back(text);

}

void PauseMenu::update() {
  for (auto e : entities_)
    e->update();
}


#endif //PACMAN_PAUSEMENU_H

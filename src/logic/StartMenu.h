#ifndef PACMAN_STARTMENU_H
#define PACMAN_STARTMENU_H

#include "State.h"
#include "utils/Utils.h"
#include "../view/state/StateManager.h"
#include <utility>

typedef std::shared_ptr<Entity> EntityPtr;

class StartMenu : public State {
  std::vector<EntityPtr> entities_;
  std::weak_ptr<StateManager> state_manager_;

public:
  StartMenu(std::shared_ptr<AbstractFactory> factory, std::weak_ptr<StateManager> state_manager)
  : State(factory), state_manager_(state_manager) {};
  void initialize() override;
  void update() override;
  void handleAction(Action action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::STARTMENU;
  }
  void makeTitle();
};

void StartMenu::initialize() {
  std::string text, font;
  // Title
  text = "Start Menu";
  font = "assets/font/Pacfont.ttf";
  auto text_ = factory_->createText({0, 0}, text, font, 70);
  entities_.push_back(text_);

  // Subtext
  text = "Press S to start";
  font = "assets/font/liber.ttf";
  text_ = factory_->createText({0, -0.4}, text, font, 30);
  entities_.push_back(text_);
}

void StartMenu::makeTitle() {
  std::string title = "Game Over";
  std::string font = "assets/font/Pacfont.ttf";
  auto text = factory_->createText({0, 0}, title, font, 70);
  entities_.push_back(text);
}

void StartMenu::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_STARTMENU_H
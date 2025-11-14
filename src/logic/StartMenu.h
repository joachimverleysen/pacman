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
  void handleAction(GameAction action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::STARTMENU;
  }
};

inline void StartMenu::initialize() {
  TextConfig config;
  // Title
  config.text = "Welcome";
  config.font = MyFont::PACFONT;
  config.character_size = 70;
  auto text_ = factory_->createText({0, 0.8}, config);
  entities_.push_back(text_);

  // Subtext
  TextConfig sconfig;
  sconfig.text = "Press S to start playing";
  sconfig.font = MyFont::LIBER;
  text_ = factory_->createText({0, 0.4}, sconfig);
  entities_.push_back(text_);

  // Subtext2
  TextConfig sconfig2;
  sconfig2.text = "Press X to exit";
  sconfig2.font = MyFont::LIBER;
  text_ = factory_->createText({0, 0.3}, sconfig2);
  entities_.push_back(text_);
}

inline void StartMenu::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_STARTMENU_H
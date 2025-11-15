#ifndef PACMAN_PAUSEMENU_H
#define PACMAN_PAUSEMENU_H

#include "State.h"
#include "utils/Utils.h"
#include "utils/TextConfig.h"
#include <utility>

typedef std::shared_ptr<Entity> EntityPtr;
class PauseMenu : public State {
  std::vector<EntityPtr> entities_;

public:
  PauseMenu(std::shared_ptr<AbstractFactory> factory) : State(factory) {};
  void initialize() override;
  void update() override;
  void handleAction(GameAction action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::PAUSE;
  }
};

inline void PauseMenu::initialize() {

  TextConfig config;
  // Title
  config.text = "Pause Menu";
  config.font = MyFont::PACFONT;
  config.character_size = 70;
  auto text_ = factory_->createText({0, 0}, config);
  entities_.push_back(text_);

  // Subtext
  TextConfig sconfig;
  sconfig.text = "Press SPACE to continue";
  sconfig.font = MyFont::LIBER;
  text_ = factory_->createText({0, -0.4}, sconfig);
  entities_.push_back(text_);

  // Subtext 2
  TextConfig sconfig2;
  sconfig2.text = "Press Q to exit";
  sconfig2.font = MyFont::LIBER;
  text_ = factory_->createText({0, -0.5}, sconfig2);
  entities_.push_back(text_);
}

inline void PauseMenu::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_PAUSEMENU_H

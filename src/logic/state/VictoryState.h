#ifndef PACMAN_VICTORYSCREEN_H
#define PACMAN_VICTORYSCREEN_H

#include "State.h"
#include "../utils/Utils.h"
#include <utility>

typedef std::shared_ptr<Entity> EntityPtr;

class VictoryState : public State {
  std::vector<EntityPtr> entities_;

public:
  VictoryState(std::shared_ptr<AbstractFactory> factory) : State(factory) {};
  void initialize() override;
  void update() override;
  void handleAction(GameAction action) override {}
  [[nodiscard]] StateNS::Type getType() const override {
    return StateNS::Type::VICTORY;
  }
};

inline void VictoryState::initialize() {
  TextConfig config;
  // Title
  config.text = "Victory";
  config.font = MyFont::PACFONT;
  config.character_size = 70;
  auto text_ = factory_->createText({0, 0}, config);
  entities_.push_back(text_);

  // Subtext
  TextConfig sconfig;
  sconfig.text = "Press SPACE for the next level";
  sconfig.font = MyFont::LIBER;
  text_ = factory_->createText({0, -0.4}, sconfig);
  entities_.push_back(text_);
  // Subtext 2
  TextConfig sconfig2;
  sconfig2.text = "Press Q to go to Start Menu";
  sconfig2.font = MyFont::LIBER;
  text_ = factory_->createText({0, -0.7}, sconfig2);
  entities_.push_back(text_);
}

inline void VictoryState::update() {
  for (auto e : entities_)
    e->update();
}

#endif // PACMAN_VICTORYSCREEN_H

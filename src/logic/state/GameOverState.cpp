#include "GameOverState.h"
#include "../Score.h"

void GameOverState::initialize() {
  TextConfig config;
  // Title
  config.text = "Game Over";
  config.font = MyFont::PACFONT;
  config.character_size = 70;
  auto text_ = factory_->createText({0, 0.5}, config);
  entities_.push_back(text_);

  // Score
  TextConfig score_config;
  // Title
  score_config.text = "Score: " + std::to_string(Score::getInstance()->getValue());
  score_config.font = MyFont::LIBER;
  score_config.character_size = 50;
  score_config.fill_color = {255, 0, 0};
  text_ = factory_->createText({0, 0.0}, score_config);
  entities_.push_back(text_);

  // Subtext
  TextConfig sconfig;
  sconfig.text = "Press Q to go to Start Menu";
  sconfig.font = MyFont::LIBER;
  text_ = factory_->createText({0, -0.6}, sconfig);
  entities_.push_back(text_);
}

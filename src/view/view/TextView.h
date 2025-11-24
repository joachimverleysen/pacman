#ifndef TEXTVIEW_H

#include "../../logic/entity/layout/Text.h"
#include "EntityView.h"
#include "TextDrawable.h"
#include <memory>
#include <string>

class TextView : public EntityView {
  std::weak_ptr<Text> text_entity_;
  std::shared_ptr<TextDrawable> text_drawable_;

public:
  TextView(std::weak_ptr<Text> text, std::shared_ptr<TextDrawable> drawable)
      : EntityView(text),
      text_entity_(text),
        text_drawable_(drawable) {}

  void setText(const std::string &text) { text_drawable_->setText(text); }

  void update() override { setText(text_entity_.lock()->getText()); }

  void draw(sf::RenderWindow& window) override { text_drawable_->draw(window);}


};
#endif // !TEXTVIEW_H

#include "Renderer.h"
#include <memory>

// Renderer is a friend of EntityFactory.

void Renderer::render() {
  updateViews();

  for (auto &v : factory_.lock()->views_) {
    if (!v.lock()->isActive())
      v.lock()->draw(window_);
  }
}

void Renderer::updateViews() {
  for (auto &v : factory_.lock()->views_) {
    if (!v.lock()->isActive())
      removeView(v);
  }
}

void Renderer::removeView(std::weak_ptr<EntityView> view) {
  auto &vec = factory_.lock()->views_;
  for (auto it = vec.begin(); it != vec.end();) {
    if (auto view = it->lock()) {
      if (!view->isActive()) {
        it = vec.erase(it);

      } else {
        ++it;
      }
    } else { // Expired weak ptr
      it = vec.erase(it);
    }
  }
}

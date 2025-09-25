#include "Renderer.h"

void Renderer::render() {
  for (auto &v : factory_.lock()->getViews()) {
    v.lock()->draw(window_);
  }
}

void Renderer::onEntitiesUpdate() {}

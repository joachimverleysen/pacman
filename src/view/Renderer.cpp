#include "Renderer.h"

void Renderer::render() {
  for (auto &v : factory_.lock()->getViews()) {
    if (!v.lock()->isActive())
      continue;
    v.lock()->draw(window_);
  }
}

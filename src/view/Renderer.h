#ifndef RENDERER
#define RENDERER
#include "../model/World.h"
#include "EntityView.h"
#include "EntityViewFactory.h"
#include <memory>

#include <vector>
class Renderer {
private:
  std::weak_ptr<World> world_;
  sf::RenderWindow &window_;
  sf::Sprite background_sprite_;
  sf::Texture background_texture_;
  std::shared_ptr<EntityViewFactory> factory_;

public:
  Renderer(sf::RenderWindow &window);
  void renderEntities();
  void render();
  void update();
  void setFactory(std::shared_ptr<EntityViewFactory> &factory);

  const FilePath &getFileTextures() const;
};
#endif // !RENDERER

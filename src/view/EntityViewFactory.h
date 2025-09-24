#include "../model/World.h"
#include "../model/entity/Entity.h"
#include "EntityView.h"
#include <memory>
#include <utility>
#include <vector>

#ifndef ENTITY_VIEW_FACTORY_H
#define ENTITY_VIEW_FACTORY_H

class EntityViewFactory : public Observer {
  World& world_;
  std::vector<std::weak_ptr<EntityView>> views_;

public:
explicit EntityViewFactory(World& world);
  void createEntityView(std::weak_ptr<Entity>);
  void onAddedEntity(std::weak_ptr<Entity>);
  [[nodiscard]] const std::vector<std::weak_ptr<EntityView>> &getViews() const;
  void update() override;
};

#endif // !ENTITY_VIEW_FACTORY_H

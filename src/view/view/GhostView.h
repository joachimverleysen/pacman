#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H


#include "EntityView.h"
#include "../../logic/entity/Ghost.h"

class GhostView : public EntityView {
public:
  GhostView(std::weak_ptr<Ghost> ghost,
            std::unique_ptr<DrawableInterface> drawable);

};


#endif //PACMAN_GHOSTVIEW_H

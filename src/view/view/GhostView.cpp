#include "GhostView.h"

GhostView::GhostView(std::weak_ptr<Ghost> ghost,
                     std::unique_ptr<DrawableInterface> drawable)
                     : EntityView(ghost, std::move(drawable)) {

}

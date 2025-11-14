#ifndef PACMAN_PAUSESTATEVIEW_H
#define PACMAN_PAUSESTATEVIEW_H


#include "StateView.h"

class PauseMenu;
class PauseStateView : public StateView {
public:

  PauseStateView(std::shared_ptr<PauseMenu> state);
};


#endif //PACMAN_PAUSESTATEVIEW_H

#ifndef PACMAN_DISPATCHER_H
#define PACMAN_DISPATCHER_H

#include "../logic/utils/AbstractDispatcher.h"
#include "audio/SoundPlayer.h"


class Dispatcher : public AbstractDispatcher {
public:
  void handle(FruitEatenEvent &event) override;;

 void handle(GhostEatenEvent &event) override;;

  void handle(CoinEatenEvent &event) override;;

  void handle(FrightenGhostsEvent &event) override;

  void handle(PacmanDiesEvent &event) override;

  void handle(NewLevelEvent &event) override;
};

#endif //PACMAN_DISPATCHER_H

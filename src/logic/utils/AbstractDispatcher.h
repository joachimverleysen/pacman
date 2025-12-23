#ifndef PACMAN_ABSTRACTDISPATCHER_H
#define PACMAN_ABSTRACTDISPATCHER_H

class PacmanDiesEvent;
class GhostEatenEvent;
class FruitEatenEvent;
class CoinEatenEvent;
class FrightenGhostsEvent;
class NewLevelEvent;

class AbstractDispatcher {
public:
  virtual ~AbstractDispatcher() = default;

public:
  virtual void handle(PacmanDiesEvent& event) = 0;
  virtual void handle(FruitEatenEvent& event) = 0;
  virtual void handle(GhostEatenEvent& event) = 0;
  virtual void handle(CoinEatenEvent& event) = 0;
  virtual void handle(FrightenGhostsEvent& event) = 0;
  virtual void handle(NewLevelEvent & event) = 0;
};

#endif //PACMAN_ABSTRACTDISPATCHER_H
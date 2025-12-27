#ifndef PACMAN_VISITOR_H
#define PACMAN_VISITOR_H

class PacmanDiesEvent;
class GhostEatenEvent;
class FruitEatenEvent;
class CoinEatenEvent;
class FrightenGhostsEvent;
class NewLevelEvent;

class Visitor {
public:
  virtual ~Visitor() = default;

  virtual void visit(CoinEatenEvent &event) = 0;
  virtual void visit(FruitEatenEvent &event) = 0;
  virtual void visit(GhostEatenEvent &event) = 0;
  virtual void visit(FrightenGhostsEvent &event) = 0;
  virtual void visit(PacmanDiesEvent &event) = 0;
  virtual void visit(NewLevelEvent &event) = 0;
};

#endif //PACMAN_VISITOR_H
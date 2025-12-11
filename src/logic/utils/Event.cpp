#include "Event.h"
#include "Visitor.h"

void CoinEatenEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void FruitEatenEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void GhostEatenEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void FrightenGhostsEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void PacmanDiesEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

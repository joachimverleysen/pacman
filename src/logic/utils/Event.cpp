#include "Event.h"
#include "Visitor.h"
#include "AbstractDispatcher.h"

void CoinEatenEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void CoinEatenEvent::accept(AbstractDispatcher &dispatcher) {
  dispatcher.handle(*this);
}

void FruitEatenEvent::accept(AbstractDispatcher &dispatcher) {
  dispatcher.handle(*this);
}

void FruitEatenEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void GhostEatenEvent::accept(AbstractDispatcher &dispatcher) {
  dispatcher.handle(*this);
}

void GhostEatenEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void FrightenGhostsEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void FrightenGhostsEvent::accept(AbstractDispatcher &dispatcher) {
  dispatcher.handle(*this);
}

void PacmanDiesEvent::accept(AbstractDispatcher &dispatcher) {
  dispatcher.handle(*this);
}

void PacmanDiesEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

void NewLevelEvent::accept(AbstractDispatcher &dispatcher) {
  dispatcher.handle(*this);
}

void NewLevelEvent::accept(Visitor &visitor) {
  visitor.visit(*this);
}

#ifndef OBSERVER_H
#define OBSERVER_H

class CoinEatenEvent;
class FruitEatenEvent;
class GhostEatenEvent;

class Observer {
  bool active_{true};

public:
  virtual ~Observer() = default;
  virtual void update() = 0;
  virtual void onDeactivate();
  [[nodiscard]] bool isActive() const { return active_; };
  virtual void handle(CoinEatenEvent &event) {};
  virtual void handle(FruitEatenEvent &event) {};
  virtual void handle(GhostEatenEvent &event) {};
};

#endif // OBSERVER_H

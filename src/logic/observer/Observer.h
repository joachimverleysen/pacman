#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
  bool active_{true};

public:
  virtual ~Observer() = default;
  virtual void update() = 0;
  virtual void onDeactivate();
  [[nodiscard]] bool isActive() const { return active_; };
};

#endif // OBSERVER_H

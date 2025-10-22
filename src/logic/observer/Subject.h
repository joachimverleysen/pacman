#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

class Subject {
protected:
  std::vector<std::shared_ptr<Observer>> observers_;

public:
  virtual ~Subject() { observers_.clear(); }

  void addObserver(const std::shared_ptr<Observer>& observer) {
    observers_.push_back(observer);
  }

  [[maybe_unused]] void removeObserver(const std::shared_ptr<Observer>& observer) {
    assert(observer != nullptr);
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end());
  }

  void notifyObservers() {
    for (const auto& observer : observers_) {
      observer->update();
    }
  }
};

#endif // SUBJECT_H

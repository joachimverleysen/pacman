#ifndef DOODLEJUMP_SUBJECT_H
#define DOODLEJUMP_SUBJECT_H

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

  void addObserver(std::shared_ptr<Observer> observer) {
    observers_.push_back(observer);
  }

  void removeObserver(std::shared_ptr<Observer> observer) {
    assert(observer != nullptr);
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end());
  }

  void notifyObservers() {
    for (auto observer : observers_) {
      observer->update();
    }
  }
};

#endif // DOODLEJUMP_SUBJECT_H

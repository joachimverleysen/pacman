#ifndef STATE_H
#define STATE_H

#include "../../view/view/EntityView.h"
#include <memory>
#include <vector>

class State : public Subject {
public:
  virtual void initialize() = 0;
  virtual void update() = 0;
};

#endif // !STATE_H

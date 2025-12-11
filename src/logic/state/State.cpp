#include "State.h"

State::State(std::shared_ptr<AbstractFactory> factory)
: factory_(std::move(factory)) {

}

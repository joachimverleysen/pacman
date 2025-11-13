#include "State.h"

State::State(std::unique_ptr <AbstractFactory> factory)
: factory_(std::move(factory)) {

}

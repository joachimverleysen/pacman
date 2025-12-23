#include "State.h"

State::State(std::shared_ptr<AbstractFactory> factory,
             std::shared_ptr<AbstractDispatcher> dispatcher)
: factory_(std::move(factory)), dispatcher_(std::move(dispatcher))
 {}

State::State(std::shared_ptr<AbstractFactory> factory)
: factory_(std::move(factory))
{}

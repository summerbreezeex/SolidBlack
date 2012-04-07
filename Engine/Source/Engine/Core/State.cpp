#include "State.h"

State::State(const std::string& name) :
        stateManager(nullptr),
        name(name),
        active(true) {
}

void State::begin(StateManager* stateManager) {
    assert(!this->stateManager);
    this->stateManager = stateManager;
}

void State::end() {
    assert(stateManager);
    stateManager = nullptr;
}

void State::setAsInactive() {
    active = false;
}

const std::string& State::getName() const {
    return name;
}

bool State::isActive() const {
    return active;
}

StateManager* State::getStateManager() {
    return stateManager;
}
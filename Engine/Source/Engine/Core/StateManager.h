#pragma once

#include <OgreTimer.h>

#include "Engine/Core/State.h"

class Engine;

class StateManager {
public:
    StateManager();

    void execute(Engine* engine);

    void queueState(State* state);

    void logicUpdate();
    void frameUpdate(Ogre::Real frameDelta);

private:
    Ogre::Real getSeconds();

    Engine* engine;

    Ogre::Timer timer;
    Ogre::Real timeStep;
    Ogre::Real lastFrameUpdate;

    StatePtr activeState;

    std::queue<StatePtr> stateQueue;
};
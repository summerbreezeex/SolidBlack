#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include "Engine/Core/Engine.h"

#include "StateManager.h"

StateManager::StateManager() :
        engine(nullptr),
        timeStep(1.0 / 20.0),
        lastFrameUpdate(0.0) {
}

void StateManager::execute(Engine* engine) {
    this->engine = engine;

    logicUpdate();

    Ogre::Real currentTime = getSeconds();
    Ogre::Real accumulator = 0.0, frameDelta = 0.0;
    lastFrameUpdate = currentTime;

    while (activeState) {
        Ogre::Real newTime = getSeconds();
        Ogre::Real deltaTime = newTime - currentTime;
        currentTime = newTime;

        accumulator += deltaTime;
        frameDelta += deltaTime;

        while (accumulator >= timeStep && activeState) {
            logicUpdate();

            frameDelta = 0.0;
            accumulator -= timeStep;
        }

        frameUpdate(frameDelta / timeStep);
    }
}

void StateManager::queueState(State* state) {
    stateQueue.push(StatePtr(state));
}

void StateManager::logicUpdate() {
    if (activeState && !activeState->isActive()) {
        engine->logInfo("Ending state '" + activeState->getName() + "'...");
        activeState->end();

        activeState.reset();
    }

    if (!activeState && !stateQueue.empty()) {
        activeState = stateQueue.front();
        stateQueue.pop();

        engine->logInfo("Beginning state '" + activeState->getName() + "'...");
        activeState->begin(this);
    }

    if (activeState) {
        activeState->logicUpdate(timeStep);
    }
}

void StateManager::frameUpdate(Ogre::Real frameDelta) {
    Ogre::WindowEventUtilities::messagePump();
    engine->getInputHandler()->capture();

    if (engine->getRenderWindow()->isClosed()) {
        activeState.reset();
    } else {
        if (activeState) {
            activeState->frameUpdate(frameDelta);
        }

        if (!engine->getRoot()->renderOneFrame(getSeconds() - lastFrameUpdate)) {
            activeState.reset();
        }

        lastFrameUpdate = getSeconds();
    }
}

Ogre::Real StateManager::getSeconds() {
    return (Ogre::Real)engine->getRoot()->getTimer()->getMilliseconds() / 1000.0;
}
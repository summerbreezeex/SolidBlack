#pragma once

#include <OISKeyboard.h>

#include "Engine/Actor/Scene.h"
#include "Engine/Core/State.h"

class Engine;

class TestState :
            public State,
            public OIS::KeyListener {
public:
    TestState(Engine* engine);

    void begin(StateManager* stateManager);
    void end();

    void logicUpdate(Ogre::Real timeStep);
    void frameUpdate(Ogre::Real frameDelta);

    bool keyPressed(const OIS::KeyEvent& event);
    bool keyReleased(const OIS::KeyEvent& event);

private:
    Engine* engine;

    Scene scene;
};
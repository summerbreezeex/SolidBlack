#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Core/Engine.h"
#include "Engine/Core/InputHandler.h"
#include "Engine/Core/StateManager.h"

#include "Game/Component/SolidBlackComponentModule.h"

#include "TestState.h"

TestState::TestState(Engine* engine) :
        State("Test"),
        engine(engine),
        scene("primary", engine) {
}

void TestState::begin(StateManager* stateManager) {
    State::begin(stateManager);

    engine->getInputHandler()->registerKeyListener(this);

    scene.getComponentFactory()->registerModule<SolidBlackComponentModule>();
    scene.loadActorsFromFile("SceneDebug.json");
}

void TestState::end() {
    engine->getInputHandler()->unregisterKeyListener(this);

    State::end();
}

void TestState::logicUpdate(Ogre::Real timeStep) {
    scene.logicUpdate(timeStep);
}

void TestState::frameUpdate(Ogre::Real frameDelta) {
    scene.frameUpdate(frameDelta);
}

bool TestState::keyPressed(const OIS::KeyEvent& event) {
    return true;
}

bool TestState::keyReleased(const OIS::KeyEvent& event) {
    if (event.key == OIS::KC_ESCAPE) {
        setAsInactive();
    }

    if (event.key == OIS::KC_F5) {
        scene.saveActorsToFile("SceneDebug.json");
    }

    return true;
}
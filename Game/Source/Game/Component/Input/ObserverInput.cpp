#include <OgreVector3.h>

#include "Engine/Actor/Actor.h"

#include "Game/Component/Logical/ObserverLogic.h"
#include "Game/Component/Visual/ObserverCamera.h"

#include "ObserverInput.h"

std::string ObserverInput::typeName = "ObserverInput";

ObserverInput::ObserverInput() :
        observerCamera(nullptr),
        observerLogic(nullptr) {
    addImplementedTypeName(typeName);
}

void ObserverInput::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    observerCamera = actor->findComponentOfType<ObserverCamera>();
    observerLogic = actor->findComponentOfType<ObserverLogic>();
}

void ObserverInput::detachFromActor() {
    observerCamera = nullptr;
    observerLogic = nullptr;

    Super::detachFromActor();
}

bool ObserverInput::mouseMoved(const OIS::MouseEvent& event) {
    if (!observerCamera) {
        return true;
    }

    observerCamera->increaseYawVelocity(event.state.X.rel * -0.0025);
    observerCamera->increasePitchVelocity(event.state.Y.rel * -0.0025);

    if (event.state.Z.rel > 0) {
        observerCamera->increaseSpeed();
    } else if (event.state.Z.rel < 0) {
        observerCamera->decreaseSpeed();
    }

    return true;
}

bool ObserverInput::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    if (!observerLogic) {
        return true;
    }

    if (buttonId == OIS::MB_Left) {
        observerLogic->debugAction1();
    }

    if (buttonId == OIS::MB_Right) {
        observerLogic->debugAction2();
    }

    if (buttonId == OIS::MB_Middle) {
        observerLogic->debugAction3();
    }

    return true;
}

bool ObserverInput::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    return true;
}

bool ObserverInput::keyPressed(const OIS::KeyEvent& event) {
    if (!observerCamera) {
        return true;
    }

    if (observerCamera && event.key == OIS::KC_W) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
    }

    if (observerCamera && event.key == OIS::KC_S) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::UNIT_Z);
    }

    if (observerCamera && event.key == OIS::KC_A) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_X);
    }

    if (observerCamera && event.key == OIS::KC_D) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::UNIT_X);
    }

    if (observerCamera && event.key == OIS::KC_Q) {
        observerCamera->addLocalRollDirection(1.0);
    }

    if (observerCamera && event.key == OIS::KC_E) {
        observerCamera->addLocalRollDirection(-1.0);
    }

    return true;
}

bool ObserverInput::keyReleased(const OIS::KeyEvent& event) {
    if (!observerCamera) {
        return true;
    }

    if (observerCamera && event.key == OIS::KC_W) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::UNIT_Z);
    }

    if (observerCamera && event.key == OIS::KC_S) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
    }

    if (observerCamera && event.key == OIS::KC_A) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::UNIT_X);
    }

    if (observerCamera && event.key == OIS::KC_D) {
        observerCamera->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_X);
    }

    if (observerCamera && event.key == OIS::KC_Q) {
        observerCamera->addLocalRollDirection(-1.0);
    }

    if (observerCamera && event.key == OIS::KC_E) {
        observerCamera->addLocalRollDirection(1.0);
    }

    return true;
}
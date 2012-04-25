#include <OgreVector3.h>

#include "Engine/Actor/Actor.h"

#include "Game/Component/Logical/ObserverLogic.h"
#include "Game/Component/Visual/ObserverCamera.h"

#include "ObserverInput.h"

ComponentClassDef(ObserverInput)

ObserverInput::ObserverInput(ComponentFactory* factory) :
        InputComponent(factory) {
    addDependency(&observerCamera);
    addDependency(&observerLogic);
}

bool ObserverInput::mouseMoved(const OIS::MouseEvent& event) {
    if (!observerCamera) {
        return true;
    }

    auto observerCameraComponent = observerCamera.getComponent();

    observerCameraComponent->increaseYawVelocity(event.state.X.rel * -0.0025);
    observerCameraComponent->increasePitchVelocity(event.state.Y.rel * -0.0025);

    if (event.state.Z.rel > 0) {
        observerCameraComponent->increaseSpeed();
    } else if (event.state.Z.rel < 0) {
        observerCameraComponent->decreaseSpeed();
    }

    return true;
}

bool ObserverInput::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    if (!observerLogic) {
        return true;
    }

    auto observerLogicComponent = observerLogic.getComponent();

    if (buttonId == OIS::MB_Left) {
        observerLogicComponent->debugAction1();
    }

    if (buttonId == OIS::MB_Right) {
        observerLogicComponent->debugAction2();
    }

    if (buttonId == OIS::MB_Middle) {
        observerLogicComponent->debugAction3();
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

    auto observerCameraComponent = observerCamera.getComponent();

    if (event.key == OIS::KC_W) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
    }

    if (event.key == OIS::KC_S) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::UNIT_Z);
    }

    if (event.key == OIS::KC_A) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_X);
    }

    if (event.key == OIS::KC_D) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::UNIT_X);
    }

    if (event.key == OIS::KC_Q) {
        observerCameraComponent->addLocalRollDirection(1.0);
    }

    if (event.key == OIS::KC_E) {
        observerCameraComponent->addLocalRollDirection(-1.0);
    }

    return true;
}

bool ObserverInput::keyReleased(const OIS::KeyEvent& event) {
    if (!observerCamera) {
        return true;
    }

    auto observerCameraComponent = observerCamera.getComponent();

    if (event.key == OIS::KC_W) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::UNIT_Z);
    }

    if (event.key == OIS::KC_S) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
    }

    if (event.key == OIS::KC_A) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::UNIT_X);
    }

    if (event.key == OIS::KC_D) {
        observerCameraComponent->addLocalMoveDirection(Ogre::Vector3::NEGATIVE_UNIT_X);
    }

    if (event.key == OIS::KC_Q) {
        observerCameraComponent->addLocalRollDirection(-1.0);
    }

    if (event.key == OIS::KC_E) {
        observerCameraComponent->addLocalRollDirection(1.0);
    }

    return true;
}
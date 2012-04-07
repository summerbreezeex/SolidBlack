#include "Engine/Actor/Scene.h"
#include "Engine/Core/Engine.h"
#include "Engine/Core/InputHandler.h"

#include "InputComponent.h"

InputComponent::InputComponent() {
    setFamily("Input");
}

void InputComponent::enterScene(Scene* scene) {
    Super::enterScene(scene);

    InputHandler* inputHandler = scene->getEngine()->getInputHandler();
    inputHandler->registerKeyListener(this);
    inputHandler->registerMouseListener(this);
}

void InputComponent::leaveScene() {
    Scene* scene = getScene();

    InputHandler* inputHandler = scene->getEngine()->getInputHandler();
    inputHandler->unregisterKeyListener(this);
    inputHandler->unregisterMouseListener(this);

    Super::leaveScene();
}

bool InputComponent::mouseMoved(const OIS::MouseEvent& event) {
    return true;
}

bool InputComponent::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    return true;
}

bool InputComponent::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    return true;
}

bool InputComponent::keyPressed(const OIS::KeyEvent& event) {
    return true;
}

bool InputComponent::keyReleased(const OIS::KeyEvent& event) {
    return true;
}
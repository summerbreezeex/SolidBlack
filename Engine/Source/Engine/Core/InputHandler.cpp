#include <OgreRoot.h>
#include <OgreRenderWindow.h>

#include "InputHandler.h"

InputHandler::InputHandler() :
        inputManager(nullptr),
        mouse(nullptr),
        keyboard(nullptr),
        hWnd(0) {
}

InputHandler::~InputHandler() {
    if (inputManager) {
        if (mouse) {
            inputManager->destroyInputObject(mouse);
            mouse = nullptr;
        }

        if (keyboard) {
            inputManager->destroyInputObject(keyboard);
            keyboard = nullptr;
        }

        OIS::InputManager::destroyInputSystem(inputManager);
        inputManager = nullptr;
    }
}

void InputHandler::initialize(Ogre::Root* root, Ogre::RenderWindow* renderWindow) {
    renderWindow->getCustomAttribute("WINDOW", &hWnd);

    OIS::ParamList paramList;
    paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

    inputManager = OIS::InputManager::createInputSystem(paramList);

    mouse = (OIS::Mouse*)inputManager->createInputObject(OIS::OISMouse, true);
    keyboard = (OIS::Keyboard*)inputManager->createInputObject(OIS::OISKeyboard, true);

    mouse->setEventCallback(this);
    keyboard->setEventCallback(this);
}

void InputHandler::registerMouseListener(OIS::MouseListener* mouseListener) {
    assert(std::find(mouseListeners.begin(), mouseListeners.end(), mouseListener) == mouseListeners.end());
    mouseListeners.push_back(mouseListener);
}

void InputHandler::unregisterMouseListener(OIS::MouseListener* mouseListener) {
    assert(std::find(mouseListeners.begin(), mouseListeners.end(), mouseListener) != mouseListeners.end());
    mouseListeners.erase(std::remove(mouseListeners.begin(), mouseListeners.end(), mouseListener), mouseListeners.end());
}

void InputHandler::registerKeyListener(OIS::KeyListener* keyListener) {
    assert(std::find(keyListeners.begin(), keyListeners.end(), keyListener) == keyListeners.end());
    keyListeners.push_back(keyListener);
}

void InputHandler::unregisterKeyListener(OIS::KeyListener* keyListener) {
    assert(find(keyListeners.begin(), keyListeners.end(), keyListener) != keyListeners.end());
    keyListeners.erase(std::remove(keyListeners.begin(), keyListeners.end(), keyListener), keyListeners.end());
}

void InputHandler::setWindowExtents(int width, int height) {
    const OIS::MouseState& mouseState = mouse->getMouseState();
    mouseState.width = width;
    mouseState.height = height;
}

void InputHandler::capture() {
    mouse->capture();
    keyboard->capture();
}

bool InputHandler::mouseMoved(const OIS::MouseEvent& event) {
    foreach (mouseListener, mouseListeners) {
        (*mouseListener)->mouseMoved(event);
    }
    return true;
}

bool InputHandler::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    foreach (mouseListener, mouseListeners) {
        (*mouseListener)->mousePressed(event, buttonId);
    }
    return true;
}

bool InputHandler::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    foreach (mouseListener, mouseListeners) {
        (*mouseListener)->mouseReleased(event, buttonId);
    }
    return true;
}

bool InputHandler::keyPressed(const OIS::KeyEvent& event) {
    foreach (keyListener, keyListeners) {
        (*keyListener)->keyPressed(event);
    }
    return true;
}

bool InputHandler::keyReleased(const OIS::KeyEvent& event) {
    foreach (keyListener, keyListeners) {
        (*keyListener)->keyReleased(event);
    }
    return true;
}
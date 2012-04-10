#pragma once

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISMouse.h>
#include <OISKeyboard.h>

#include "Engine/StlCommon.h"

class InputHandler :
            public OIS::MouseListener,
            public OIS::KeyListener {
public:
    InputHandler();
    ~InputHandler();

    void initialize(Ogre::Root* root, Ogre::RenderWindow* renderWindow);

    void registerMouseListener(OIS::MouseListener* mouseListener);
    void unregisterMouseListener(OIS::MouseListener* mouseListener);

    void registerKeyListener(OIS::KeyListener* keyListener);
    void unregisterKeyListener(OIS::KeyListener* keyListener);

    void setWindowExtents(int width, int height);
    void capture();

    bool mouseMoved(const OIS::MouseEvent& event);
    bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);
    bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);

    bool keyPressed(const OIS::KeyEvent& event);
    bool keyReleased(const OIS::KeyEvent& event);

private:
    OIS::InputManager* inputManager;
    OIS::Mouse* mouse;
    OIS::Keyboard* keyboard;
    unsigned long hWnd;

    std::vector<OIS::MouseListener*> mouseListeners;
    std::vector<OIS::KeyListener*> keyListeners;
};
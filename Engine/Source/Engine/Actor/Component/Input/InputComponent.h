#pragma once

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "Engine/Actor/Component/Component.h"

class InputComponent :
            public Component,
            public OIS::KeyListener,
            public OIS::MouseListener {
    typedef Component Super;
public:
    InputComponent();
    virtual ~InputComponent() { }

    virtual void enterScene(Scene* scene);
    virtual void leaveScene();

    virtual bool mouseMoved(const OIS::MouseEvent& event);
    virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);
    virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);

    virtual bool keyPressed(const OIS::KeyEvent& event);
    virtual bool keyReleased(const OIS::KeyEvent& event);
};
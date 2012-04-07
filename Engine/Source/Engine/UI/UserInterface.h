#pragma once

#include <OISKeyboard.h>
#include <OISMouse.h>

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include "Engine/UI/View.h"

class InputHandler;

class UserInterface :
            public OIS::KeyListener,
            public OIS::MouseListener {
public:
    UserInterface();
    ~UserInterface();

    void initialise(Ogre::RenderWindow* renderWindow, Ogre::SceneManager* sceneManager, InputHandler* inputHandler);
    void cleanUp();

    void addView(const std::string& name, View* view);
    void removeView(const std::string& name);
    void removeView(View* view);

    void removeAllViews();
    void removeMarkedViews();

    bool hasView(const std::string& name);

    bool mouseMoved(const OIS::MouseEvent& event);
    bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);
    bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);

    bool keyPressed(const OIS::KeyEvent& event);
    bool keyReleased(const OIS::KeyEvent& event);

    MyGUI::Gui* getGUI();

private:
    bool initialised;

    MyGUI::Gui* gui;
    MyGUI::OgrePlatform* platform;

    Ogre::RenderWindow* renderWindow;

    InputHandler* inputHandler;

    std::map<std::string, ViewPtr> views;
};
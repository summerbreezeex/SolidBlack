#pragma once

#include <OgrePrerequisites.h>
#include <OgreWindowEventUtilities.h>

#include "Engine/StlCommon.h"
#include "Engine/Core/InputHandler.h"
#include "Engine/Core/Logged.h"
#include "Engine/Core/StateManager.h"
#include "Engine/Threading/TaskPool.h"

class Engine :
            public Logged,
            public Ogre::WindowEventListener {
public:
    Engine();
    ~Engine();

    bool initialize();

    void execute();

    Ogre::Root* getRoot();
    Ogre::RenderWindow* getRenderWindow();

    InputHandler* getInputHandler();
    StateManager* getStateManager();

    TaskPool* getTaskPool();

private:
    void loadResourcesConfig(const std::string& resourcesConfigFile);

    void windowResized(Ogre::RenderWindow* renderWindow);
    void windowClosed(Ogre::RenderWindow* renderWindow);

    std::unique_ptr<Ogre::Root> root;
    Ogre::RenderWindow* renderWindow;

    InputHandler inputHandler;
    StateManager stateManager;
    TaskPool taskPool;
};
#pragma once

#include <OgreWindowEventUtilities.h>

#include "Engine/Core/InputHandler.h"
#include "Engine/Core/StateManager.h"
#include "Engine/Core/TaskPool.h"

class Engine :
            public Ogre::WindowEventListener {
public:
    Engine();
    ~Engine();

    bool initialise();

    void execute();

    void logInfo(const std::string& message);
    void logWarning(const std::string& message);

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

    Ogre::Log* log;
};
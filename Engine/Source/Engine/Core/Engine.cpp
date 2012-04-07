#include <OgreConfigFile.h>
#include <OgreLog.h>
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>

#include "Engine/Actor/Component/DefaultComponentModule.h"
#include "Engine/Core/Settings.h"

#include "Engine.h"

Engine::Engine() :
        root(new Ogre::Root(Settings::pluginsConfigFile, Settings::configFile, Settings::ogreLogFile)),
        renderWindow(nullptr) {
}

Engine::~Engine() {
    if (log) {
        Ogre::LogManager::getSingleton().destroyLog(log);
        log = nullptr;
    }

    if (renderWindow) {
        Ogre::WindowEventUtilities::removeWindowEventListener(renderWindow, this);
    }
}

bool Engine::initialise() {
    log = Ogre::LogManager::getSingleton().createLog(Settings::engineLogFile);

    loadResourcesConfig(Settings::resourcesConfigFile);

    if (root->restoreConfig() || root->showConfigDialog()) {
        renderWindow = root->initialise(true, "SolidBlack");
    } else {
        return false;
    }

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(10);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    Ogre::WindowEventUtilities::addWindowEventListener(renderWindow, this);

    inputHandler.initialise(root.get(), renderWindow);
    windowResized(renderWindow);

    return true;
}

void Engine::execute() {
    //stateManager.queueState(new SceneEditorState(this));
    //stateManager.queueState(new TestState(this));
    stateManager.execute(this);
}

void Engine::logInfo(const std::string& message) {
    if (log) {
        log->logMessage(message);
    }
}

void Engine::logWarning(const std::string& message) {
    if (log) {
        log->logMessage(std::string("WARNING: ") + message);
    }
}

Ogre::Root* Engine::getRoot() {
    return root.get();
}

Ogre::RenderWindow* Engine::getRenderWindow() {
    return renderWindow;
}

InputHandler* Engine::getInputHandler() {
    return &inputHandler;
}

StateManager* Engine::getStateManager() {
    return &stateManager;
}

TaskPool* Engine::getTaskPool() {
    return &taskPool;
}

void Engine::loadResourcesConfig(const std::string& resourcesConfigFile) {
    Ogre::ConfigFile configFile;
    configFile.load(resourcesConfigFile);

    auto secIterator = configFile.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (secIterator.hasMoreElements()) {
        secName = secIterator.peekNextKey();

        auto settings = secIterator.getNext();
        for (auto i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
}

void Engine::windowResized(Ogre::RenderWindow* renderWindow) {
    unsigned int width = 0, height = 0, depth = 0;
    int left = 0, top = 0;

    renderWindow->getMetrics(width, height, depth, left, top);
    inputHandler.setWindowExtents(width, height);
}

void Engine::windowClosed(Ogre::RenderWindow* renderWindow) {
}
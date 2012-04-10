#include "Engine/Core/Engine.h"
#include "Engine/Core/InputHandler.h"
#include "Engine/Core/Settings.h"

#include "UserInterface.h"

UserInterface::UserInterface() :
        initialized(false),
        gui(nullptr),
        platform(nullptr),
        renderWindow(nullptr),
        inputHandler(nullptr) {
}

UserInterface::~UserInterface() {
    if (initialized) {
        cleanUp();
    }
}

void UserInterface::initialize(Ogre::RenderWindow* renderWindow, Ogre::SceneManager* sceneManager, InputHandler* inputHandler) {
    platform = new MyGUI::OgrePlatform();
    platform->initialise(renderWindow, sceneManager, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Settings::myGuiLogFile);

    gui = new MyGUI::Gui();
    gui->initialise("Core.xml");

    this->inputHandler = inputHandler;
    inputHandler->registerKeyListener(this);
    inputHandler->registerMouseListener(this);

    this->renderWindow = renderWindow;

    initialized = true;
}

void UserInterface::cleanUp() {
    removeAllViews();

    if (gui) {
        gui->shutdown();
        delete gui;
        gui = nullptr;
    }

    if (platform) {
        platform->shutdown();
        delete platform;
        platform = nullptr;
    }

    inputHandler->unregisterKeyListener(this);
    inputHandler->unregisterMouseListener(this);
    inputHandler = nullptr;

    initialized = false;
}

void UserInterface::addView(const std::string& name, View* view) {
    //Engine::logInfo(std::string("Adding view '") + name + "'...");

    view->setName(name);
    view->setUserInterface(this);

    views[name] = ViewPtr(view);

    view->loadLayout();
    view->initialize();
    view->resize(renderWindow->getWidth(), renderWindow->getHeight());
}

void UserInterface::removeView(const std::string& name) {
    //Engine::logInfo(std::string("Removing view '") + name + "'...");

    auto it = views.find(name);

    View* view = (*it).second.get();
    view->destroy();
    view->unloadLayout();

    views.erase(it);
}

void UserInterface::removeView(View* view) {
    removeView(view->getName());
}

void UserInterface::removeAllViews() {
    std::vector<View*> viewsToRemove;

    foreach (viewPair, views) {
        viewsToRemove.push_back((*viewPair).second.get());
    }

    foreach (view, viewsToRemove) {
        removeView(*view);
    }

    assert(views.size() == 0);
}

void UserInterface::removeMarkedViews() {
    std::vector<View*> viewsToRemove;

    foreach (viewPair, views) {
        View* view = (*viewPair).second.get();

        if (view->isMarkedForRemoval()) {
            viewsToRemove.push_back(view);
        }
    }

    foreach (view, viewsToRemove) {
        removeView(*view);
    }
}

bool UserInterface::hasView(const std::string& name) {
    return views.find(name) != views.end();
}

bool UserInterface::mouseMoved(const OIS::MouseEvent& event) {
    MyGUI::InputManager::getInstance().injectMouseMove(event.state.X.abs, event.state.Y.abs, event.state.Z.abs);
    return true;
}

bool UserInterface::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    MyGUI::InputManager::getInstance().injectMousePress(event.state.X.abs, event.state.Y.abs, MyGUI::MouseButton::Enum(buttonId));
    return true;
}

bool UserInterface::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId) {
    MyGUI::InputManager::getInstance().injectMouseRelease(event.state.X.abs, event.state.Y.abs, MyGUI::MouseButton::Enum(buttonId));
    return true;
}

bool UserInterface::keyPressed(const OIS::KeyEvent& event) {
    MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(event.key), event.text);
    return true;
}

bool UserInterface::keyReleased(const OIS::KeyEvent& event) {
    MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(event.key));
    return true;
}

MyGUI::Gui* UserInterface::getGUI() {
    return gui;
}
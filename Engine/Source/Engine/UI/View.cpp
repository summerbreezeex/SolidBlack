#include "View.h"

View::View() :
        userInterface(nullptr),
        markedForRemoval(false) {
}

View::View(const std::string& layoutName) :
        layoutName(layoutName),
        userInterface(nullptr),
        markedForRemoval(false) {
}

void View::loadLayout() {
    assert(widgets.size() == 0);

    if (layoutName != "") {
        widgets = MyGUI::LayoutManager::getInstance().loadLayout(layoutName);
    }
}

void View::unloadLayout() {
    assert(widgets.size() != 0);

    MyGUI::LayoutManager::getInstance().unloadLayout(widgets);
}

void View::addWidget(const MyGUI::WidgetPtr& widget) {
    widgets.push_back(widget);
}

UserInterface* View::getUserInterface() {
    return userInterface;
}

void View::setUserInterface(UserInterface* userInterface) {
    this->userInterface = userInterface;
}

const std::string& View::getName() const {
    return name;
}

void View::setName(const std::string& name) {
    this->name = name;
}

void View::markForRemoval() {
    markedForRemoval = true;
}

bool View::isMarkedForRemoval() const {
    return markedForRemoval;
}
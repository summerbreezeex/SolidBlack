#pragma once

#include <MyGUI.h>

#include "Engine/StlCommon.h"

class UserInterface;

class View {
public:
    View();
    View(const std::string& layoutName);
    virtual ~View() { }

    virtual void initialize() { }
    virtual void destroy() { }

    virtual void resize(int width, int height) { }

    void loadLayout();
    void unloadLayout();

    void addWidget(const MyGUI::WidgetPtr& widget);

    UserInterface* getUserInterface();
    void setUserInterface(UserInterface* userInterface);

    const std::string& getName() const;
    void setName(const std::string& name);

    void markForRemoval();
    bool isMarkedForRemoval() const;

private:
    std::string layoutName;
    std::string name;
    bool markedForRemoval;

    UserInterface* userInterface;

    MyGUI::VectorWidgetPtr widgets;
};

typedef std::shared_ptr<View> ViewPtr;
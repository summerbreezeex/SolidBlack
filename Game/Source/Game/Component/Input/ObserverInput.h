#pragma once

#include "Engine/Actor/Component/Input/InputComponent.h"

class ObserverCamera;
class ObserverLogic;

class ObserverInput :
            public InputComponent {
public:
    ComponentClass

    ObserverInput(ComponentFactory* factory);

    bool mouseMoved(const OIS::MouseEvent& event);
    bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);
    bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonId);

    bool keyPressed(const OIS::KeyEvent& event);
    bool keyReleased(const OIS::KeyEvent& event);

private:
    ComponentDependency<ObserverCamera> observerCamera;
    ComponentDependency<ObserverLogic> observerLogic;
};
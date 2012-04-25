#pragma once

#include "Engine/Actor/Component/Logical/LogicalComponent.h"

class ObserverCamera;

class ObserverLogic :
            public LogicalComponent {
public:
    ComponentClass

    ObserverLogic(ComponentFactory* factory);

    void debugAction1();
    void debugAction2();
    void debugAction3();

private:
    ComponentDependency<ObserverCamera> observerCamera;
};
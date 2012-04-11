#pragma once

#include "Engine/Actor/Component/Logical/LogicalComponent.h"

class ObserverCamera;

class ObserverLogic :
            public LogicalComponent {
    typedef LogicalComponent Super;
public:
    static std::string typeName;

    ObserverLogic();

    void debugAction1();
    void debugAction2();
    void debugAction3();

private:
    ComponentDependency<ObserverCamera> observerCamera;
};
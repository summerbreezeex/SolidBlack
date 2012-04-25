#pragma once

#include "Engine/Actor/Component/Component.h"

class PhysicalComponent :
            public Component {
public:
    ComponentClass

    PhysicalComponent(ComponentFactory* factory);
    virtual ~PhysicalComponent() { }
};
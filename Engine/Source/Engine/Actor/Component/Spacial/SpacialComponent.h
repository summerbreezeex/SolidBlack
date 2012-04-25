#pragma once

#include "Engine/Actor/Component/Component.h"

class SpacialComponent :
            public Component {
public:
    ComponentClass

    SpacialComponent(ComponentFactory* factory);
    virtual ~SpacialComponent() { }
};
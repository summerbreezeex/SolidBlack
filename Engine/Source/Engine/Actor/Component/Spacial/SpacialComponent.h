#pragma once

#include "Engine/Actor/Component/Component.h"

class SpacialComponent :
            public Component {
public:
    SpacialComponent(ComponentFactory* factory);
    virtual ~SpacialComponent() { }
};
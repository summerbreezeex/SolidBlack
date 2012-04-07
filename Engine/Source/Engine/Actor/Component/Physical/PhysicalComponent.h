#pragma once

#include "Engine/Actor/Component/Component.h"

class PhysicalComponent :
            public Component {
public:
    PhysicalComponent();
    virtual ~PhysicalComponent() { }
};
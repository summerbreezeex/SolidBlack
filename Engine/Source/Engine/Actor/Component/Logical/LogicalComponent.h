#pragma once

#include "Engine/Actor/Component/Component.h"

class LogicalComponent :
            public Component {
public:
    ComponentClass

    LogicalComponent(ComponentFactory* factory);
    virtual ~LogicalComponent() { }
};
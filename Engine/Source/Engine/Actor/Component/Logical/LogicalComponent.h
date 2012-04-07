#pragma once

#include "Engine/Actor/Component/Component.h"

class LogicalComponent :
            public Component {
public:
    LogicalComponent();
    virtual ~LogicalComponent() { }
};
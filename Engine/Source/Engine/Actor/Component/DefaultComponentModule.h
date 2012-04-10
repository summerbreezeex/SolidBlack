#pragma once

#include "Engine/Actor/Component/ComponentModule.h"

class DefaultComponentModule :
            public ComponentModule {
public:
    void registerComponents(ComponentFactory* factory);
};
#pragma once

#include "Engine/Actor/Component/ComponentModule.h"

class SolidBlackComponentModule :
            public ComponentModule {
public:
    void registerComponents(ComponentFactory* factory);
};
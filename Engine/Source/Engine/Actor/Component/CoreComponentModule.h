#pragma once

#include "Engine/Actor/Component/ComponentModule.h"

class CoreComponentModule :
            public ComponentModule {
public:
    void registerComponents(ComponentFactory* factory);
    void registerCode(ScriptInterpreter* interpreter);
};
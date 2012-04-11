#pragma once

#include "Engine/Scripting/ScriptModule.h"

class ComponentFactory;

class ComponentModule :
        ScriptModule {
public:
    virtual void registerComponents(ComponentFactory* factory) = 0;
};
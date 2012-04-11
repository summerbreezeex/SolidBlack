#pragma once

#include "Engine/Scripting/ScriptModule.h"

class CoreScriptModule :
            public ScriptModule {
public:
    void registerCode(ScriptInterpreter* interpreter);
};
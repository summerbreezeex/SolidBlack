#pragma once

class ScriptInterpreter;

class ScriptModule {
public:
    virtual void registerCode(ScriptInterpreter* interpreter) = 0;
};
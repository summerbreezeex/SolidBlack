#pragma once

#include <luabind/luabind.hpp>

#include "Engine/StlCommon.h"

class ScriptInterpreter {
public:
    ScriptInterpreter();
    ~ScriptInterpreter();

private:
    lua_State* luaState;
};
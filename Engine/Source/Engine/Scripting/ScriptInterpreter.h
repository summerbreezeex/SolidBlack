#pragma once

#include <luabind/luabind.hpp>

#include "Engine/StlCommon.h"

class ScriptInterpreter {
public:
    ScriptInterpreter();
    ~ScriptInterpreter();

    template <typename T>
    void registerModule();

    void execute(const std::string& code);

    void loadScript(const std::string scriptName);

    lua_State* getLuaState();

private:
    lua_State* luaState;

    std::set<std::string> loadedScripts;
};

#include "ScriptInterpreter.inl"
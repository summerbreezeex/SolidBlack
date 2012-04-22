#pragma once

#include <luabind/luabind.hpp>

#include "Engine/StlCommon.h"

typedef luabind::object LuaObject;

class ScriptInterpreter {
public:
    ScriptInterpreter();
    ~ScriptInterpreter();

    template <typename T>
    void registerModule();

    void execute(const std::string& code);

    void loadScript(const std::string scriptName);

    lua_State* getLuaState();

    std::string getErrorMessage();

private:
    lua_State* luaState;

    std::set<std::string> loadedScripts;
};

#include "ScriptInterpreter.inl"
#include "ScriptInterpreter.h"

ScriptInterpreter::ScriptInterpreter() :
        luaState(luaL_newstate()) {
}

ScriptInterpreter::~ScriptInterpreter() {
    lua_close(luaState);
}
#include <OgreResourceGroupManager.h>

extern "C" {
    #include <lualib.h>
    #include <lauxlib.h>
}

#include "Engine/Scripting/CoreScriptModule.h"

#include "ScriptInterpreter.h"

ScriptInterpreter::ScriptInterpreter() :
        luaState(luaL_newstate()) {
    luaL_openlibs(luaState);

    luabind::open(luaState);
    
    registerModule<CoreScriptModule>();
}

ScriptInterpreter::~ScriptInterpreter() {
    lua_close(luaState);
}

void ScriptInterpreter::execute(const std::string& code) {
    if (luaL_dostring(luaState, code.c_str())) {
        throw std::runtime_error("Script error");
    }
}

void ScriptInterpreter::loadScript(const std::string scriptName) {
    std::string fileName = scriptName + ".lua";
    if (loadedScripts.find(fileName) == loadedScripts.end()) {
        std::string code = Ogre::ResourceGroupManager::getSingleton().openResource(fileName)->getAsString();
        execute(code);

        loadedScripts.insert(fileName);
    }
}

lua_State* ScriptInterpreter::getLuaState() {
    return luaState;
}
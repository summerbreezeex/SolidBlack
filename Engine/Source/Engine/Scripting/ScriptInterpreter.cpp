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
        throw std::runtime_error(getErrorMessage());
    }
}

void ScriptInterpreter::loadScript(const std::string scriptName) {
    if (loadedScripts.find(scriptName) == loadedScripts.end()) {
        std::string code = Ogre::ResourceGroupManager::getSingleton().openResource(scriptName)->getAsString();

        try {
            execute(code);
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Failed to load script '" + scriptName + "': " + e.what());
        }

        loadedScripts.insert(scriptName);
    }
}

lua_State* ScriptInterpreter::getLuaState() {
    return luaState;
}

std::string ScriptInterpreter::getErrorMessage() {
    const char* errorMessage = lua_tostring(luaState, -1);
    lua_pop(luaState, 1); 
    return std::string(errorMessage);
}
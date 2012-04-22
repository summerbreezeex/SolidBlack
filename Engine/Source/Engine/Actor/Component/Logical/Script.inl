#pragma once

template <typename Ret>
Ret Script::invokeFunction(const std::string& functionName) {
    try {
        return luabind::call_function<Ret>(scriptInterpreter->getLuaState(), functionName.c_str());
    } catch (const luabind::error&) {
        throw std::runtime_error("Error occurred in function '" + functionName + "' in '" + *scriptName + "': " + scriptInterpreter->getErrorMessage());
    }
}
#pragma once

template <typename Ret>
Ret Script::invokeFunction(const std::string& functionName) {
    try {
        return luabind::call_function<Ret>(scriptInterpreter->getLuaState(), functionName.c_str());
    } catch (const luabind::error&) {
        throw std::runtime_error("Error occurred in function '" + functionName + "' in '" + scriptName.getValue() + "': " + scriptInterpreter->getErrorMessage());
    }
}

template <typename Ret>
Ret Script::invokeMethod(const std::string& methodName) {
    try {
        return luabind::call_member<Ret>(scriptObject, methodName.c_str());
    } catch (const luabind::error&) {
        throw std::runtime_error("Error occurred in method '" + methodName + "' in '" + scriptName.getValue() + "': " + scriptInterpreter->getErrorMessage());
    }
}

template <typename Ret, typename T0>
Ret Script::invokeMethod(const std::string& methodName, const T0& a0) {
    try {
        return luabind::call_member<Ret>(scriptObject, methodName.c_str(), a0);
    } catch (const luabind::error&) {
        throw std::runtime_error("Error occurred in method '" + methodName + "' in '" + scriptName.getValue() + "': " + scriptInterpreter->getErrorMessage());
    }
}
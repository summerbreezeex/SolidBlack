#pragma once

template <typename T>
void ScriptInterpreter::registerModule() {
    T module;
    module.registerCode(this);
}
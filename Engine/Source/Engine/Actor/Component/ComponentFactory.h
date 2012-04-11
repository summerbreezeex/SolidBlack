#pragma once

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/Component.h"

class ComponentFactory {
public:
    ComponentFactory(ScriptInterpreter* scriptInterpreter);

    template <class T>
    void registerModule();

    template <class T>
    void registerComponent();

    Component* createComponent(const std::string& typeName);

    ScriptInterpreter* getScriptInterpreter();

private:
    template <class T>
    static T* newComponent();

    ScriptInterpreter* scriptInterpreter;

    std::map<std::string, ComponentConstructor> constructors;
};

#include "ComponentFactory.inl"
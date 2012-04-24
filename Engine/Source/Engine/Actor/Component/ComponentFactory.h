#pragma once

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/Component.h"

class Scene;
class ScriptInterpreter;

class ComponentFactory {
public:
    ComponentFactory(Scene* scene);

    template <class T>
    void registerModule();

    template <class T>
    void registerComponent();

    Component* createComponent(const std::string& typeName);

    Scene* getScene();

private:
    template <class T>
    static T* newComponent();

    Scene* scene;
    ScriptInterpreter* scriptInterpreter;

    std::map<std::string, ComponentConstructor> constructors;
};

#include "ComponentFactory.inl"
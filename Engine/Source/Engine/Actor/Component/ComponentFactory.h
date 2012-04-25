#pragma once

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/Component.h"

class Scene;
class ScriptInterpreter;

typedef std::function<Component*()> ComponentConstructor;

class ComponentFactory :
            Logged {
public:
    ComponentFactory(Scene* scene);

    template <class T>
    void registerModule();

    template <class T, class B>
    void registerComponent();

    template <class T>
    void registerBaseComponent(ComponentFamily::Enum family);

    template <class T, class B>
    void registerAbstractComponent();

    Component* createComponent(const std::string& typeName);

    ComponentTypeData* getTypeData(const std::string& typeName);

    Scene* getScene();

private:
    Scene* scene;
    ScriptInterpreter* scriptInterpreter;

    std::map<std::string, ComponentConstructor> constructors;
    std::map<std::string, std::shared_ptr<ComponentTypeData>> typeDataMap;
};

#include "ComponentFactory.inl"
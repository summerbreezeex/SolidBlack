#pragma once

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/Component.h"

class Scene;

typedef std::function<Component*()> ComponentConstructor;

class ComponentFactory :
            Logged {
public:
    ComponentFactory(Scene* scene);

    template <class ModuleType>
    void registerModule();

    template <class ComponentType>
    void registerBaseComponent(ComponentFamily::Enum family);

    template <class ComponentType, class SuperType>
    void registerAbstractComponent();

    template <class ComponentType, class SuperType>
    void registerComponent();

    Component* createComponent(const std::string& typeName);

    ComponentTypeData* getTypeData(const std::string& typeName);

    Scene* getScene();

private:
    template <class ComponentType>
    void throwIfRegistered();

    template <class ComponentType>
    void throwIfNotRegistered();

    Scene* scene;
    ScriptInterpreter* scriptInterpreter;

    std::vector<std::string> registeredTypeNames;
    std::map<std::string, ComponentConstructor> constructors;
    std::map<std::string, std::shared_ptr<ComponentTypeData>> typeDataMap;
};

#include "ComponentFactory.inl"
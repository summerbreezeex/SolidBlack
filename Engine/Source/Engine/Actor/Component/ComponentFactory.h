#pragma once

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/Component.h"

class Scene;

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

    ComponentTypeInfo* getTypeInfo(const std::string& typeName);

    Scene* getScene();

private:
    void throwIfRegistered(const std::string& typeName);
    void throwIfNotRegistered(const std::string& typeName);
    
    Scene* scene;
    ScriptInterpreter* scriptInterpreter;

    std::map<std::string, std::shared_ptr<ComponentTypeInfo>> typeInfoMap;
};

#include "ComponentFactory.inl"
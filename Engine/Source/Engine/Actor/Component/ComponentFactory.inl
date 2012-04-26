#pragma once

template <class ModuleType>
void ComponentFactory::registerModule() {
    ModuleType module;
    module.registerComponents(this);
    module.registerCode(scriptInterpreter);
}

template <class ComponentType>
void ComponentFactory::registerBaseComponent(ComponentFamily::Enum family) {
    auto typeName = getComponentTypeName<ComponentType>();

    throwIfRegistered(typeName);
    
    auto typeInfo = std::make_shared<ComponentTypeInfo>(typeName, family);
    registeredTypeInfo[typeName] = typeInfo;
    
    logInfo("Registered base type '" + typeInfo->getFullTypeName() + "'");
}

template <class ComponentType, class SuperType>
void ComponentFactory::registerAbstractComponent() {
    auto typeName = getComponentTypeName<ComponentType>();
    auto superTypeName = getComponentTypeName<SuperType>();

    throwIfRegistered(typeName);
    throwIfNotRegistered(superTypeName);

    auto superTypeInfo = registeredTypeInfo[superTypeName].get();
    auto typeInfo = std::make_shared<ComponentTypeInfo>(typeName, superTypeInfo);
    registeredTypeInfo[typeName] = typeInfo;

    logInfo("Registered abstract type '" + typeInfo->getFullTypeName() + "'");
}

template <class ComponentType, class SuperType>
void ComponentFactory::registerComponent() {
    auto typeName = getComponentTypeName<ComponentType>();
    auto superTypeName = getComponentTypeName<SuperType>();

    throwIfRegistered(typeName);
    throwIfNotRegistered(superTypeName);

    auto superTypeInfo = registeredTypeInfo[superTypeName].get();
    auto typeInfo = std::make_shared<ComponentTypeInfo>(typeName, superTypeInfo, [this] { return new ComponentType(this); });
    registeredTypeInfo[typeName] = typeInfo;

    logInfo("Registered type '" + typeInfo->getFullTypeName() + "'");
}
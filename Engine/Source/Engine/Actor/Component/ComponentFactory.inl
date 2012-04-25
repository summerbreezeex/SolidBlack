#pragma once

template <class ModuleType>
void ComponentFactory::registerModule() {
    ModuleType module;
    module.registerComponents(this);
    module.registerCode(scriptInterpreter);
}

template <class ComponentType>
void ComponentFactory::registerBaseComponent(ComponentFamily::Enum family) {
    throwIfRegistered<ComponentType>();

    auto typeData = std::make_shared<ComponentTypeData>(ComponentType::typeName, family);
    typeDataMap[ComponentType::typeName] = typeData;
    
    registeredTypeNames.push_back(ComponentType::typeName);
    logInfo("Registered base type '" + typeData->getFullTypeName() + "'");
}

template <class ComponentType, class SuperType>
void ComponentFactory::registerAbstractComponent() {
    throwIfRegistered<ComponentType>();
    throwIfNotRegistered<SuperType>();

    auto superTypeData = typeDataMap[SuperType::typeName].get();
    auto typeData = std::make_shared<ComponentTypeData>(ComponentType::typeName, superTypeData);
    typeDataMap[ComponentType::typeName] = typeData;

    registeredTypeNames.push_back(ComponentType::typeName);
    logInfo("Registered type '" + typeData->getFullTypeName() + "'");
}

template <class ComponentType, class SuperType>
void ComponentFactory::registerComponent() {
    registerAbstractComponent<ComponentType, SuperType>();

    constructors[ComponentType::typeName] = [this] { return new ComponentType(this); };
}

template <class ComponentType>
void ComponentFactory::throwIfRegistered() {
    if (std::find(registeredTypeNames.begin(), registeredTypeNames.end(), ComponentType::typeName) != registeredTypeNames.end()) {
        throw std::runtime_error("Component type '" + ComponentType::typeName + "' is already registered");
    }
}

template <class ComponentType>
void ComponentFactory::throwIfNotRegistered() {
    if (std::find(registeredTypeNames.begin(), registeredTypeNames.end(), ComponentType::typeName) == registeredTypeNames.end()) {
        throw std::runtime_error("Component type '" + ComponentType::typeName + "' is not registered");
    }
}
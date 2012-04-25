#pragma once

template <class T>
void ComponentFactory::registerModule() {
    T module;
    module.registerComponents(this);
    module.registerCode(scriptInterpreter);
}

template <class T, class B>
void ComponentFactory::registerComponent() {
    assert(constructors.find(T::typeName) == constructors.end());

    auto typeData = new ComponentTypeData();
    auto baseTypeData = typeDataMap[B::typeName];
    typeData->setFamily(baseTypeData->getFamily());

    foreach (baseTypeName, baseTypeData->getBaseTypeNames()) {
        typeData->addBaseTypeName(*baseTypeName);
    }

    typeData->setDerivedTypeName(T::typeName);

    typeDataMap[T::typeName] = std::shared_ptr<ComponentTypeData>(typeData);

    constructors[T::typeName] = [this] { return new T(this); };
}

template <class T>
void ComponentFactory::registerBaseComponent(ComponentFamily::Enum family) {
    assert(constructors.find(T::typeName) == constructors.end());

    auto typeData = new ComponentTypeData();
    typeData->setFamily(family);
    typeData->addBaseTypeName(T::typeName);

    typeDataMap[T::typeName] = std::shared_ptr<ComponentTypeData>(typeData);
}

template <class T, class B>
void ComponentFactory::registerAbstractComponent() {
    assert(constructors.find(T::typeName) == constructors.end());

    auto typeData = new ComponentTypeData();
    auto baseTypeData = typeDataMap[B::typeName];
    typeData->setFamily(baseTypeData->getFamily());

    foreach (baseTypeName, baseTypeData->getBaseTypeNames()) {
        typeData->addBaseTypeName(*baseTypeName);
    }

    typeData->addBaseTypeName(T::typeName);

    typeDataMap[T::typeName] = std::shared_ptr<ComponentTypeData>(typeData);
}
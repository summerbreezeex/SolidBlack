#pragma once

template <class T>
void ComponentFactory::registerModule() {
    T module;
    module.registerComponents(this);
    module.registerCode(scriptInterpreter);
}

template <class T, class B>
void ComponentFactory::registerComponent() {
    registerAbstractComponent<T, B>();
    constructors[T::typeName] = [this] { return new T(this); };
}

template <class T>
void ComponentFactory::registerBaseComponent(ComponentFamily::Enum family) {
    assert(constructors.find(T::typeName) == constructors.end());

    typeDataMap[T::typeName] = std::make_shared<ComponentTypeData>(T::typeName, family);
}

template <class T, class B>
void ComponentFactory::registerAbstractComponent() {
    assert(constructors.find(T::typeName) == constructors.end());

    auto superTypeData = typeDataMap[B::typeName].get();
    typeDataMap[T::typeName] = std::make_shared<ComponentTypeData>(T::typeName, superTypeData);
}
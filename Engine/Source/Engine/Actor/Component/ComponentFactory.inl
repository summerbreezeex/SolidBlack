#pragma once

template <class T>
void ComponentFactory::registerModule() {
    T module;
    module.registerComponents(this);
    module.registerCode(scriptInterpreter);
}

template <class T>
void ComponentFactory::registerComponent() {
    assert(constructors.find(T::typeName) == constructors.end());
    constructors[T::typeName] = (ComponentConstructor)newComponent<T>;
}

template <class T>
T* ComponentFactory::newComponent() {
    return new T();
}
#pragma once

template <class T>
T* Actor::findComponentOfType() {
    auto typeName = getComponentTypeName<T>();
    return dynamic_cast<T*>(findComponentOfType(typeName));
}

template <class T>
const std::vector<T*> Actor::findComponentsOfType() {
    auto typeName = getComponentTypeName<T>();
    auto components = findComponentsOfType(typeName);

    std::vector<T*> resultingComponents;
    foreach (component, components) {
        resultingComponents.push_back(dynamic_cast<T*>(*component));
    }

    return resultingComponents;
}
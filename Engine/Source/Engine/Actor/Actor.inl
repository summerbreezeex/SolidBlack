#pragma once

template <class T>
T* Actor::findComponentOfType() {
    return dynamic_cast<T*>(findComponentOfType(T::typeName));
}

template <class T>
const std::vector<T*> Actor::findComponentsOfType() {
    auto components = findComponentsOfType(T::typeName);

    std::vector<T*> resultingComponents;
    foreach (component, components) {
        resultingComponents.push_back(dynamic_cast<T*>(*component));
    }

    return resultingComponents;
}
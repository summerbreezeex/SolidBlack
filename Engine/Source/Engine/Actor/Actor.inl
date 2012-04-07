#pragma once

template <class T>
T* Actor::findComponentOfType() {
    auto it = componentImplementedTypes.find(T::typeName);

    if (it == componentImplementedTypes.end()) {
        return nullptr;
    } else {
        std::vector<Component*> components = (*it).second;

        T* castedComponent = dynamic_cast<T*>(components[0]);
        assert(castedComponent);

        return castedComponent;
    }
}

template <class T>
const std::vector<T*> Actor::findComponentsOfType() {
    auto it = componentImplementedTypes.find(T::typeName);

    std::vector<T*> resultingComponents;

    if (it == componentImplementedTypes.end()) {
        return resultingComponents;
    } else {
        std::vector<Component*> components = (*it).second;

        foreach (component, components) {
            T* castedComponent = dynamic_cast<T*>(*component);
            assert(castedComponent);

            resultingComponents.push_back(castedComponent);
        }

        return resultingComponents;
    }
}
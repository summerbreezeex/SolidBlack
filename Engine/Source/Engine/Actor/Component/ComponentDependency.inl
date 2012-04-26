#pragma once

template <typename T>
ComponentDependency<T>::ComponentDependency() :
        component(nullptr) {
}

template <typename T>
void ComponentDependency<T>::setComponent(Component* component) {
    this->component = (T*)component;
}

template <typename T>
T* ComponentDependency<T>::getComponent() {
    return (T*)component;
}

template <typename T>
const T* ComponentDependency<T>::getComponent() const {
    return (T*)component;
}

template <typename T>
Component* ComponentDependency<T>::getBaseComponent() {
    return component;
}

template <typename T>
const std::string ComponentDependency<T>::getTypeName() const {
    return getComponentTypeName<T>();
}

template <typename T>
ComponentDependency<T>::operator bool() const {
    return component != nullptr;
}
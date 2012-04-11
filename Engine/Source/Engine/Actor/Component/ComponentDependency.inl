#pragma once

template <typename T>
ComponentDependency<T>::ComponentDependency() :
        ComponentDependencyBase(T::typeName),
        component(nullptr) {
}

template <typename T>
void ComponentDependency<T>::setComponent(Component* component) {
    this->component = (T*)component;
}

template <typename T>
T* ComponentDependency<T>::operator*() {
    return component;
}

template <typename T>
const T* ComponentDependency<T>::operator*() const {
    return component;
}

template <typename T>
ComponentDependency<T>::operator bool() const {
    return component != nullptr;
}
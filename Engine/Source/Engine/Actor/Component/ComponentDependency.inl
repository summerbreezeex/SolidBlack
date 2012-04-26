#pragma once

template <typename ComponentType>
ComponentDependency<ComponentType>::ComponentDependency() :
        component(nullptr) {
}

template <typename ComponentType>
void ComponentDependency<ComponentType>::resolve(Component* component) {
    this->component = (ComponentType*)component;
}

template <typename ComponentType>
void ComponentDependency<ComponentType>::unresolve() {
    this->component = nullptr;
}

template <typename ComponentType>
const std::string ComponentDependency<ComponentType>::getTypeName() const {
    return getComponentTypeName<ComponentType>();
}

template <typename ComponentType>
ComponentType* ComponentDependency<ComponentType>::getComponent() {
    return (ComponentType*)component;
}

template <typename ComponentType>
const ComponentType* ComponentDependency<ComponentType>::getComponent() const {
    return (ComponentType*)component;
}

template <typename ComponentType>
Component* ComponentDependency<ComponentType>::getBaseComponent() {
    return component;
}

template <typename ComponentType>
ComponentDependency<ComponentType>::operator bool() const {
    return component != nullptr;
}
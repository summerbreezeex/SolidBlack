#pragma once

template <typename T>
ComponentAttribute<T>::ComponentAttribute(const std::string& name, const T& value) :
        ComponentAttributeBase(name),
        value(value) {
}

template <typename T>
T& ComponentAttribute<T>::operator*() {
    return value;
}

template <typename T>
const T& ComponentAttribute<T>::operator*() const {
    return value;
}
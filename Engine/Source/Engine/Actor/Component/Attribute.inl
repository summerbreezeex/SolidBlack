#pragma once

template <typename T>
Attribute<T>::Attribute(const std::string& name, const T& value) :
        AttributeBase(name),
        value(value) {
}

template <typename T>
T& Attribute<T>::operator*() {
    return value;
}

template <typename T>
const T& Attribute<T>::operator*() const {
    return value;
}
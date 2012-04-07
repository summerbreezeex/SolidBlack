#pragma once

template <typename T>
Attribute<T>::Attribute(const std::string& name, const T& value) :
        AttributeBase(name),
        value(value) {
}

template <typename T>
void Attribute<T>::setValue(const T& value) {
    this->value = value;
}

template <typename T>
T& Attribute<T>::getValue() {
    return value;
}

template <typename T>
const T& Attribute<T>::getValue() const {
    return value;
}
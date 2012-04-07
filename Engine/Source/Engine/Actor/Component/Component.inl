#pragma once

template <typename T>
bool Component::attributeIsType(const std::string& name) const {
    Attribute<T>* attribute = dynamic_cast<Attribute<T>*>(attributes[name]);
    return attribute != 0;
}

template <typename T>
void Component::setAttributeValue(const std::string& name, const T& value) {
    Attribute<T>* attribute = dynamic_cast<Attribute<T>*>(attributes[name]);

    if (attribute) {
        attribute->setValue(value);
    }
}

template <typename T>
const T* Component::getAttributeValue(const std::string& name) const {
    Attribute<T>* attribute = dynamic_cast<Attribute<T>*>(attributes[name]);

    if (attribute) {
        return &attribute->getValue();
    } else {
        return 0;
    }
}
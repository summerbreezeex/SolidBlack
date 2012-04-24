#pragma once

template <typename T>
bool Component::attributeIsType(const std::string& name) const {
    ComponentAttribute<T>* attribute = dynamic_cast<ComponentAttribute<T>*>(attributes[name]);
    return attribute != nullptr;
}

template <typename T>
void Component::setAttributeValue(const std::string& name, const T& value) {
    ComponentAttribute<T>* attribute = dynamic_cast<ComponentAttribute<T>*>(attributes[name]);

    if (attribute) {
        attribute->setValue(value);
    }
}

template <typename T>
const T* Component::getAttributeValue(const std::string& name) const {
    ComponentAttribute<T>* attribute = dynamic_cast<ComponentAttribute<T>*>(attributes[name]);

    if (attribute) {
        return &attribute->getValue();
    } else {
        return nullptr;
    }
}
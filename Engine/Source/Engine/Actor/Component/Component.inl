#pragma once

template <typename T>
bool Component::attributeIsType(const std::string& name) const {
    ComponentAttribute<T>* attribute = dynamic_cast<ComponentAttribute<T>*>(attributes[name]);
    return attribute != 0;
}

template <typename T>
void Component::setAttributeValue(const std::string& name, const T& value) {
    ComponentAttribute<T>* attribute = dynamic_cast<ComponentAttribute<T>*>(attributes[name]);

    if (attribute) {
        **attribute = value;
    }
}

template <typename T>
const T* Component::getAttributeValue(const std::string& name) const {
    ComponentAttribute<T>* attribute = dynamic_cast<ComponentAttribute<T>*>(attributes[name]);

    if (attribute) {
        return &**attribute;
    } else {
        return 0;
    }
}
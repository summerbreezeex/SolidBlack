#pragma once

template <typename AttributeType>
const AttributeType* Component::getAttributeValue(const std::string& name) const {
    auto attribute =
        dynamic_cast<ComponentAttribute<AttributeType>*>(attributes[name]);

    if (attribute) {
        return &attribute->getValue();
    } else {
        return nullptr;
    }
}

template <typename AttributeType>
void Component::setAttributeValue(const std::string& name, const AttributeType& value) {
    auto attribute =
        dynamic_cast<ComponentAttribute<AttributeType>*>(attributes[name]);

    if (attribute) {
        attribute->setValue(value);
    }
}
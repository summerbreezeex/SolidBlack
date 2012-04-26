#pragma once

template <typename AttributeType>
ComponentAttribute<AttributeType>::ComponentAttribute(const std::string& name, const AttributeType& value) :
        ComponentAttributeBase(name),
        value(value) {
}

template <typename AttributeType>
const AttributeType& ComponentAttribute<AttributeType>::getValue() const {
    return value;
}

template <typename AttributeType>
void ComponentAttribute<AttributeType>::setValue(const AttributeType& value) {
    this->value = value;
}
#pragma once

#include "Engine/StlCommon.h"

namespace Json {
    class Value;
}

class ComponentAttributeBase {
public:
    ComponentAttributeBase(const std::string& name);

    virtual void serializeToJson(Json::Value* jsonValue) const = 0;
    virtual void deserializeFromJson(const Json::Value& jsonValue) = 0;

    const std::string& getName() const;

private:
    std::string name;
};

template <typename AttributeType>
class ComponentAttribute :
            public ComponentAttributeBase {
public:
    ComponentAttribute(const std::string& name, const AttributeType& value);

    void serializeToJson(Json::Value* jsonValue) const;
    void deserializeFromJson(const Json::Value& jsonValue);

    AttributeType& getValue();
    const AttributeType& getValue() const;
    void setValue(const AttributeType& value);

private:
    AttributeType value;
};

#include "ComponentAttribute.inl"
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

template <typename T>
class ComponentAttribute :
            public ComponentAttributeBase {
public:
    ComponentAttribute(const std::string& name, const T& value);

    void serializeToJson(Json::Value* jsonValue) const;
    void deserializeFromJson(const Json::Value& jsonValue);

    T& operator*();
    const T& operator*() const;

private:
    T value;
};

#include "ComponentAttribute.inl"
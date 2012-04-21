#include "Engine/Actor/Component/Component.h"
#include "Engine/Actor/Component/ComponentFactory.h"

#include "ComponentJsonSerializer.h"

void ComponentJsonSerializer::serialize(const Component* component, Json::Value* jsonValue) {
    Json::Value& value = *jsonValue;
    value["type"] = component->getImplementedTypeNames().back();

    auto attributes = component->getAttributes();
    foreach (attribute, attributes) {
        std::string attributeName = (*attribute)->getName();
        (*attribute)->serializeToJson(&value[attributeName]);
    }
}

Component* ComponentJsonSerializer::deserialize(ComponentFactory* factory, const Json::Value& jsonValue) {
    Component* component = factory->createComponent(jsonValue["type"].asString());

    Json::Value::Members attributeNames = jsonValue.getMemberNames();
    foreach (attributeName, attributeNames) {
        if (*attributeName != "type") {
            if (ComponentAttributeBase* attribute = component->getAttribute(*attributeName)) {
                attribute->deserializeFromJson(jsonValue[*attributeName]);
            }
        }
    }

    return component;
}
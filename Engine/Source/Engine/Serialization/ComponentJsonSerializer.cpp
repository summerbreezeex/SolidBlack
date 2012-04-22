#include "Engine/Actor/Component/Component.h"
#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Actor/Component/Logical/Script.h"

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
    auto typeName = jsonValue["type"].asString();
    Component* component = factory->createComponent(typeName);

    // Scripts must be initialized before the other attributes are deserialized.
    if (typeName == "Script") {
        component->setAttributeValue("scriptName", jsonValue["scriptName"].asString()); 
        ((Script*)component)->initializeScript();
    }

    Json::Value::Members attributeNames = jsonValue.getMemberNames();
    foreach (attributeName, attributeNames) {
        if (*attributeName != "type" && *attributeName != "scriptName") {
            if (ComponentAttributeBase* attribute = component->getAttribute(*attributeName)) {
                attribute->deserializeFromJson(jsonValue[*attributeName]);
            }
        }
    }

    return component;
}
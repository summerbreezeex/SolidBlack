#pragma once

#include <json/json.h>

class Component;
class ComponentFactory;

class ComponentJsonSerializer {
public:
    static void serialize(const Component* component, Json::Value* jsonValue);
    static Component* deserialize(ComponentFactory* factory, const Json::Value& jsonValue);
};
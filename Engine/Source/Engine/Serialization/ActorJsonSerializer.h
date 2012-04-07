#pragma once

#include <json/json.h>

class Actor;
class ComponentFactory;

class ActorJsonSerializer {
public:
    static void serialize(const Actor* actor, Json::Value* jsonValue);
    static Actor* deserialize(ComponentFactory* factory, const Json::Value& jsonValue);
};
#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Serialization/ComponentJsonSerializer.h"

#include "ActorJsonSerializer.h"

void ActorJsonSerializer::serialize(const Actor* actor, Json::Value* jsonValue) {
    Json::Value& value = *jsonValue;
    value["name"] = actor->getName();

    auto components = actor->getComponents();
    foreach (component, components) {
        Json::Value componentValue;
        ComponentJsonSerializer::serialize(*component, &componentValue);
        value["components"].append(componentValue);
    }
}

Actor* ActorJsonSerializer::deserialize(ComponentFactory* factory, const Json::Value& jsonValue) {
    std::string name = jsonValue["name"].asString();
    auto actor = new Actor(name);

    Json::Value componentJsonValues = jsonValue["components"];
    int componentCount = (int)componentJsonValues.size();

    for (int i = 0; i < componentCount; ++i) {
        const Json::Value& componentJsonValue = componentJsonValues[i];

        Component* component = ComponentJsonSerializer::deserialize(factory, componentJsonValue);
        actor->addComponent(component);
    }
    actor->attachComponents();

    return actor;
}
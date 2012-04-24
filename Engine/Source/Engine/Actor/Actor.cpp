#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Core/Engine.h"

#include "Actor.h"

Actor::Actor(const std::string& name) :
        name(name),
        id(0),
        alive(true),
        scene(nullptr) {
}

void Actor::attachComponents() {
    foreach (component, components) {
        (*component)->attachToActor(this);
    }
}

void Actor::enterScene(Scene* scene) {
    assert(scene);
    assert(!this->scene);

    this->scene = scene;

    foreach (component, components) {
        if ((*component)->isValid()) {
            (*component)->enterScene(scene);
        }
        scene->addComponent((*component).get());
    }

    scene->logInfo(std::string("Actor '") + getUniqueName() + "' entering scene '" + scene->getName() + "'...");
}

void Actor::leaveScene() {
    assert(scene);

    foreach (component, components) {
        if ((*component)->isValid()) {
            (*component)->leaveScene();
        }
        scene->removeComponent((*component).get());
    }

    scene->logInfo(std::string("Actor '") + getUniqueName() + "' leaving scene '" + scene->getName() + "'...");

    id = 0;
    scene = nullptr;
}

void Actor::kill() {
    alive = false;
}

void Actor::addComponent(Component* component) {
    ComponentPtr componentPtr(component);
    components.push_back(componentPtr);
    registerImplementedTypes(component);
}

const std::vector<const Component*> Actor::getComponents() const {
    std::vector<const Component*> resultingComponents;

    foreach (component, components) {
        resultingComponents.push_back((*component).get());
    }

    return resultingComponents;
}

Component* Actor::findComponentOfType(const std::string& typeName) {
    auto components = findComponentsOfType(typeName);
    
    if (components.size() < 0) {
        return nullptr;
    } else {
        return components[0];
    }
}

const std::vector<Component*> Actor::findComponentsOfType(const std::string& typeName) {
    auto it = componentImplementedTypes.find(typeName);

    if (it == componentImplementedTypes.end()) {
        return std::vector<Component*>();
    } else {
        return (*it).second;
    }
}

const std::string& Actor::getName() const {
    return name;
}

const std::string Actor::getUniqueName() const {
    return name + ":" + Ogre::StringConverter::toString(id);
}

ActorId Actor::getId() const {
    return id;
}

void Actor::setId(ActorId id) {
    assert(this->id == 0);
    this->id = id;
}

bool Actor::isAlive() const {
    return alive;
}

Scene* Actor::getScene() {
    return scene;
}

void Actor::registerImplementedTypes(Component* component) {
    auto implementedTypeNames = component->getTypeData()->getImplementedTypeNames();

    foreach (typeName, implementedTypeNames) {
        auto it = componentImplementedTypes.find(*typeName);

        if (it == componentImplementedTypes.end()) {
            componentImplementedTypes[*typeName] = std::vector<Component*>();
        }

        componentImplementedTypes[*typeName].push_back(component);
    }
}
#include <OgrePrerequisites.h>

#include "Engine/Actor/Scene.h"

#include "Component.h"

Component::Component() :
        actor(nullptr),
        scene(nullptr),
        family("None") {
}

Component::~Component() {
    assert(!scene);
}

void Component::attachToActor(Actor* actor) {
    assert(actor);
    assert(!this->actor);

    this->actor = actor;
}

void Component::detachFromActor() {
    assert(actor);
    actor = nullptr;
}

void Component::enterScene(Scene* scene) {
    assert(actor);
    assert(scene);
    assert(!this->scene);

    this->scene = scene;
}

void Component::leaveScene() {
    assert(scene);

    scene = nullptr;
}

Actor* Component::getActor() const {
    return actor;
}

Scene* Component::getScene() const {
    return scene;
}

const std::string& Component::getFamily() const {
    return family;
}

const std::vector<std::string>& Component::getImplementedTypeNames() const {
    return implementedTypeNames;
}

const std::vector<std::string> Component::getAttributeNames() const {
    std::vector<std::string> attributeNames;

    foreach (attributePair, attributes) {
        attributeNames.push_back((*attributePair).first);
    }

    return attributeNames;
}

AttributeBase* Component::getAttribute(const std::string& name) {
    auto it = attributes.find(name);

    if (it != attributes.end()) {
        return (*it).second;
    } else {
        return 0;
    }
}

const AttributeBase* Component::getAttribute(const std::string& name) const {
    auto it = attributes.find(name);

    if (it != attributes.end()) {
        return (*it).second;
    } else {
        return 0;
    }
}

const std::vector<AttributeBase*> Component::getAttributes() const {
    std::vector<AttributeBase*> resultAttributes;

    foreach (attributePair, attributes) {
        resultAttributes.push_back((*attributePair).second);
    }

    return resultAttributes;
}

void Component::addAttribute(AttributeBase* attribute) {
    attributes[attribute->getName()] = attribute;
}

void Component::addImplementedTypeName(const std::string& implementedTypeName) {
    implementedTypeNames.push_back(implementedTypeName);
}

void Component::setFamily(const std::string& family) {
    this->family = family;
}
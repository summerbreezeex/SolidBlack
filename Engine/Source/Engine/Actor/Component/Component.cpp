#include <OgrePrerequisites.h>

#include "Engine/Actor/Scene.h"

#include "Component.h"

Component::Component(ComponentFactory* factory) :
        Logged("Component"),
        actor(nullptr),
        scene(nullptr),
        typeInfo(nullptr), // Set by ComponentTypeInfo when constructing component.
        factory(factory),
        validFlag(true) {
}

Component::~Component() {
    assert(!scene);
}

void Component::attachToActor(Actor* actor) {
    assert(actor);
    assert(!this->actor);

    this->actor = actor;

    resolveDependencies();
}

void Component::detachFromActor() {
    assert(actor);
    actor = nullptr;

    unresolveDependencies();
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

ComponentTypeInfo* Component::getTypeInfo() {
    return typeInfo;
}

const ComponentTypeInfo* Component::getTypeInfo() const {
    return typeInfo;
}

bool Component::isValid() const {
    return validFlag;
}

ComponentAttributeBase* Component::getAttribute(const std::string& name) {
    auto it = attributes.find(name);

    if (it != attributes.end()) {
        return (*it).second;
    } else {
        return nullptr;
    }
}

const ComponentAttributeBase* Component::getAttribute(const std::string& name) const {
    auto it = attributes.find(name);

    if (it != attributes.end()) {
        return (*it).second;
    } else {
        return nullptr;
    }
}

const std::vector<ComponentAttributeBase*> Component::getAttributes() {
    std::vector<ComponentAttributeBase*> resultingAttributes;

    foreach (attributePair, attributes) {
        resultingAttributes.push_back((*attributePair).second);
    }

    return resultingAttributes;
}

const std::vector<const ComponentAttributeBase*> Component::getAttributes() const {
    std::vector<const ComponentAttributeBase*> resultingAttributes;

    foreach (attributePair, attributes) {
        resultingAttributes.push_back((*attributePair).second);
    }

    return resultingAttributes;
}

void Component::addAttribute(ComponentAttributeBase* attribute) {
    attributes[attribute->getName()] = attribute;
}

void Component::addDependency(ComponentDependencyBase* dependency) {
    dependencies.push_back(dependency);
}

ComponentFactory* Component::getFactory() {
    return factory;
}

void Component::resolveDependencies() {
    foreach (dependency, dependencies) {
        auto typeName = (*dependency)->getTypeName();
        auto component = actor->findComponentOfType(typeName);
        
        if (!component) {
            validFlag = false;
            logError("Component type '" + typeInfo->getTypeName() + "' in actor '" + actor->getUniqueName() + "' requires component of type '" + typeName + "'");
        }

        (*dependency)->resolve(component);
    }
}

void Component::unresolveDependencies() {
    foreach (dependency, dependencies) {
        (*dependency)->unresolve();
    }
}
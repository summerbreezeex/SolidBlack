#include <OgrePrerequisites.h>

#include "Engine/Actor/Scene.h"

#include "Component.h"

Component::Component(ComponentFactory* factory, ComponentFamily::Enum family) :
        Logged("Component"),
        factory(factory),
        actor(nullptr),
        scene(nullptr),
        typeData(nullptr),
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

ComponentTypeData* Component::getTypeData() {
    return typeData;
}

const ComponentTypeData* Component::getTypeData() const {
    return typeData;
}

const std::vector<std::string> Component::getAttributeNames() const {
    std::vector<std::string> attributeNames;

    foreach (attributePair, attributes) {
        attributeNames.push_back((*attributePair).first);
    }

    return attributeNames;
}

ComponentAttributeBase* Component::getAttribute(const std::string& name) {
    auto it = attributes.find(name);

    if (it != attributes.end()) {
        return (*it).second;
    } else {
        return 0;
    }
}

const ComponentAttributeBase* Component::getAttribute(const std::string& name) const {
    auto it = attributes.find(name);

    if (it != attributes.end()) {
        return (*it).second;
    } else {
        return 0;
    }
}

const std::vector<ComponentAttributeBase*> Component::getAttributes() const {
    std::vector<ComponentAttributeBase*> resultAttributes;

    foreach (attributePair, attributes) {
        resultAttributes.push_back((*attributePair).second);
    }

    return resultAttributes;
}

bool Component::isValid() const {
    return validFlag;
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

        Component* component = actor->findComponentOfType(typeName);
        (*dependency)->setComponent(component);

        if (!component) {
            validFlag = false;
            logError("Component type '" + typeData->getDerivedTypeName() + "' in actor '" + actor->getUniqueName() + "' requires component of type '" + typeName + "'");
        }
    }
}

void Component::unresolveDependencies() {
    foreach (dependency, dependencies) {
        (*dependency)->setComponent(nullptr);
    }
}
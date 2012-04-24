#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Component.h"

#include "ComponentCollection.h"

void ComponentCollection::addComponent(Component* component) {
    components.push_back(component);
}

void ComponentCollection::removeComponent(Component* component) {
    auto it = find(components.begin(), components.end(), component);

    if (it != std::end(components)) {
        components.erase(it);
    }
}

void ComponentCollection::logicUpdate(Ogre::Real timeStep) {
    foreach (component, components) {
        if ((*component)->isValid()) {
            (*component)->logicUpdate(timeStep);
        }
    }
}

void ComponentCollection::frameUpdate(Ogre::Real frameDelta) {
    foreach (component, components) {
        if ((*component)->isValid()) {
            (*component)->frameUpdate(frameDelta);
        }
    }
}
#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"

class Component;

class ComponentCollection {
public:
    void addComponent(Component* component);
    void removeComponent(Component* component);

    void logicUpdate(Ogre::Real timeStep);
    void frameUpdate(Ogre::Real frameDelta);

private:
    std::vector<Component*> components;
};
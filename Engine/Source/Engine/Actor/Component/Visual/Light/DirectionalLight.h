#pragma once

#include <OgrePrerequisites.h>
#include <OgreVector3.h>

#include "Engine/Actor/Component/Visual/Light/Light.h"

class DirectionalLight :
            public Light {
public:
    DirectionalLight(ComponentFactory* factory);

    const Ogre::Vector3& getDirection() const;

private:
    Ogre::Light* createLight();

    ComponentAttribute<Ogre::Vector3> direction;
};
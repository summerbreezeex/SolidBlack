#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/Light/Light.h"

class SpotLight :
            public Light {
public:
    ComponentClass

    SpotLight(ComponentFactory* factory);

private:
    Ogre::Light* createLight();

    ComponentAttribute<Ogre::Real> innerAngle;
    ComponentAttribute<Ogre::Real> outerAngle;
    ComponentAttribute<Ogre::Real> falloff;
};
#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/Light/Light.h"

class SpotLight :
            public Light {
    typedef Light Super;
public:
    static std::string typeName;

    SpotLight();

private:
    Ogre::Light* createLight();

    Attribute<Ogre::Real> innerAngle;
    Attribute<Ogre::Real> outerAngle;
    Attribute<Ogre::Real> falloff;
};
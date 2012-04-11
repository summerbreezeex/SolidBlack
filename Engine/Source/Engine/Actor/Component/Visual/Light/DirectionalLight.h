#pragma once

#include <OgrePrerequisites.h>
#include <OgreVector3.h>

#include "Engine/Actor/Component/Visual/Light/Light.h"

class DirectionalLight :
            public Light {
    typedef Light Super;
public:
    static std::string typeName;

    DirectionalLight();

private:
    Ogre::Light* createLight();

    ComponentAttribute<Ogre::Vector3> direction;
};
#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/Light/Light.h"

class PointLight :
            public Light {
    typedef Light Super;
public:
    ComponentClass

    PointLight();

private:
    Ogre::Light* createLight();
};
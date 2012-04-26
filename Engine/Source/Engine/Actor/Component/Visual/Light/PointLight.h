#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/Light/Light.h"

class PointLight :
            public Light {
public:
    PointLight(ComponentFactory* factory);

private:
    Ogre::Light* createLight();
};
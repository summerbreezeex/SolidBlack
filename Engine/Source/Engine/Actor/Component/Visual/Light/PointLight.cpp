#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "PointLight.h"

ComponentClassDef(PointLight)

PointLight::PointLight(ComponentFactory* factory) :
        Light(factory) {
}

Ogre::Light* PointLight::createLight() {
    Ogre::Light* light = getScene()->getSceneManager()->createLight();
    light->setType(Ogre::Light::LT_POINT);

    light->setCastShadows(false);

    return light;
}
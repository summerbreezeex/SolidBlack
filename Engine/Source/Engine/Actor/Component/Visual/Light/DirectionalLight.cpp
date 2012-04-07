#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "DirectionalLight.h"

std::string DirectionalLight::typeName = "DirectionalLight";

DirectionalLight::DirectionalLight() :
        direction("direction", Ogre::Vector3::UNIT_X) {
    addImplementedTypeName(typeName);
    addAttribute(&direction);
}

Ogre::Light* DirectionalLight::createLight() {
    Ogre::Light* light = getScene()->getSceneManager()->createLight();
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(direction.getValue().normalisedCopy());

    return light;
}
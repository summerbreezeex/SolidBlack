#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "DirectionalLight.h"

ComponentClassDef(DirectionalLight)

DirectionalLight::DirectionalLight() :
        direction("direction", Ogre::Vector3::UNIT_X) {
    getTypeData()->setDerivedTypeName(typeName);
    addAttribute(&direction);
}

const Ogre::Vector3& DirectionalLight::getDirection() const {
    return direction.getValue();
}

Ogre::Light* DirectionalLight::createLight() {
    Ogre::Light* light = getScene()->getSceneManager()->createLight();
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(getDirection().normalisedCopy());

    return light;
}
#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "SpotLight.h"

SpotLight::SpotLight(ComponentFactory* factory) :
        Light(factory),
        innerAngle("innerAngle", 25.0),
        outerAngle("outerAngle", 60.0),
        falloff("falloff", 1.0) {
    addAttribute(&innerAngle);
    addAttribute(&outerAngle);
    addAttribute(&falloff);
}

Ogre::Light* SpotLight::createLight() {
    Ogre::Light* light = getScene()->getSceneManager()->createLight();
    light->setType(Ogre::Light::LT_SPOTLIGHT);

    light->setSpotlightInnerAngle(Ogre::Degree(innerAngle.getValue()));
    light->setSpotlightOuterAngle(Ogre::Degree(outerAngle.getValue()));
    light->setSpotlightFalloff(falloff.getValue());
    light->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);

    light->setCastShadows(true);

    return light;
}
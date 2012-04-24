#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "Light.h"

ComponentClassDef(Light)

Light::Light() :
        enabled("enabled", true),
        diffuseColour("diffuseColour", Ogre::ColourValue::White),
        specularColour("specularColour", Ogre::ColourValue::White),
        attenuation("attenuation", Ogre::Vector4(7.0, 1.0, 0.7, 1.8)),
        light(nullptr) {
    getTypeData()->addBaseTypeName(typeName);
    addAttribute(&enabled);
    addAttribute(&diffuseColour);
    addAttribute(&specularColour);
    addAttribute(&attenuation);
}

void Light::enterScene(Scene* scene) {
    Super::enterScene(scene);

    light = createLight();

    setEnabled(isEnabled());
    setDiffuseColour(getDiffuseColour());
    setSpecularColour(getSpecularColour());
    setAttenuation(getAttenuation());

    getSceneNode()->attachObject(light);
}

void Light::leaveScene() {
    getSceneNode()->detachObject(light);
    getScene()->getSceneManager()->destroyLight(light);
    light = nullptr;

    Super::leaveScene();
}

bool Light::isEnabled() const {
    return enabled.getValue();
}

void Light::setEnabled(bool enabled) {
    if (light) {
        light->setVisible(enabled);
        this->enabled.setValue(enabled);
    }
}

const Ogre::ColourValue& Light::getDiffuseColour() const {
    return diffuseColour.getValue();
}

void Light::setDiffuseColour(const Ogre::ColourValue& colour) {
    light->setDiffuseColour(colour);
    diffuseColour.setValue(colour);
}

const Ogre::ColourValue& Light::getSpecularColour() const {
    return specularColour.getValue();
}

void Light::setSpecularColour(const Ogre::ColourValue& colour) {
    light->setSpecularColour(colour);
    specularColour.setValue(colour);
}

const Ogre::Vector4& Light::getAttenuation() const {
    return attenuation.getValue();
}

void Light::setAttenuation(const Ogre::Vector4& attenuation) {
    light->setAttenuation(attenuation.x, attenuation.y, attenuation.z, attenuation.w);
    this->attenuation.setValue(attenuation);
}
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "Camera.h"

ComponentClassDef(Camera)

Camera::Camera(ComponentFactory* factory) :
        VisualComponent(factory),
        fov("fov", 70.0),
        camera(nullptr) {
    addAttribute(&fov);
}

void Camera::enterScene(Scene* scene) {
    VisualComponent::enterScene(scene);

    initializeCamera();

    getSceneNode()->attachObject(camera);
}

void Camera::leaveScene() {
    getSceneNode()->detachObject(camera);

    VisualComponent::leaveScene();
}

Ogre::Real Camera::getFov() const {
    return fov.getValue();
}

void Camera::setFov(Ogre::Real fov) {
    this->fov.setValue(fov);

    if (camera) {
        camera->setFOVy(Ogre::Degree(fov));
    }
}

Ogre::Vector3 Camera::getDirection() const {
    auto transformComponent = getTransform();
    if (transformComponent) {
        return transformComponent->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    } else {
        return Ogre::Vector3::NEGATIVE_UNIT_Z;
    }
}

void Camera::initializeCamera() {
    camera = getScene()->getCamera();
    camera->setFOVy(Ogre::Degree(getFov()));
}
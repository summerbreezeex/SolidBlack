#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "Camera.h"

std::string Camera::typeName = "Camera";

Camera::Camera() :
        fov("fov", 70.0),
        camera(nullptr) {
    addImplementedTypeName(typeName);
    addAttribute(&fov);
}

void Camera::enterScene(Scene* scene) {
    Super::enterScene(scene);

    initializeCamera();

    getSceneNode()->attachObject(camera);
}

void Camera::leaveScene() {
    getSceneNode()->detachObject(camera);

    Super::leaveScene();
}

Ogre::Real Camera::getFov() const {
    return fov.getValue();
}

void Camera::setFov(Ogre::Real fov) {
    this->fov.setValue(fov);

    if (camera) {
        camera->setFOVy(Ogre::Degree(getFov()));
    }
}

Ogre::Vector3 Camera::getDirection() const {
    if (getTransform()) {
        return getTransform()->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    } else {
        return Ogre::Vector3::NEGATIVE_UNIT_Z;
    }
}

void Camera::initializeCamera() {
    camera = getScene()->getCamera();
    camera->setFOVy(Ogre::Degree(getFov()));
}
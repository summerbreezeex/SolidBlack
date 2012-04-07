#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

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

    initialiseCamera();

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

void Camera::initialiseCamera() {
    camera = getScene()->getCamera();
    camera->setFOVy(Ogre::Degree(getFov()));
}
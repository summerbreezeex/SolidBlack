#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "Transform.h"

ComponentClassDef(Transform)

Transform::Transform() :
        position("position", Ogre::Vector3::ZERO),
        orientation("orientation", Ogre::Quaternion::IDENTITY),
        lastPosition(getPosition()),
        interpolatedPosition(getPosition()),
        lastOrientation(getOrientation()),
        interpolatedOrientation(getOrientation()) {
    getTypeData()->setDerivedTypeName(typeName);
    addAttribute(&position);
    addAttribute(&orientation);
}

void Transform::enterScene(Scene* scene) {
    Super::enterScene(scene);

    sceneNode = scene->getSceneManager()->getRootSceneNode()->createChildSceneNode();

    lastPosition = getPosition();
    lastOrientation = getOrientation();
}

void Transform::leaveScene() {
    sceneNode = nullptr;

    Super::leaveScene();
}

void Transform::logicUpdate(Ogre::Real timeStep) {
    lastPosition = getPosition();
    lastOrientation = getOrientation();

    sceneNode->setPosition(interpolatedPosition);
    sceneNode->setOrientation(interpolatedOrientation);
}

void Transform::frameUpdate(Ogre::Real frameDelta) {
    interpolatedPosition = lastPosition + (getPosition() - lastPosition) * frameDelta;
    interpolatedOrientation = Ogre::Quaternion::Slerp(frameDelta, lastOrientation, getOrientation());

    sceneNode->setPosition(interpolatedPosition);
    sceneNode->setOrientation(interpolatedOrientation);
}

void Transform::translate(const Ogre::Vector3& translation) {
    setPosition(getPosition() + translation);
}

void Transform::rotate(const Ogre::Vector3& axis, const Ogre::Radian& angle) {
    rotate(Ogre::Quaternion(angle, axis));
}

void Transform::rotate(Ogre::Quaternion quaternion) {
    quaternion.normalise();
    setOrientation(getOrientation() * quaternion);
}

void Transform::roll(const Ogre::Radian& amount) {
    rotate(Ogre::Quaternion(amount, Ogre::Vector3::UNIT_Z));
}

void Transform::yaw(const Ogre::Radian& amount) {
    rotate(Ogre::Quaternion(amount, Ogre::Vector3::UNIT_Y));
}

void Transform::pitch(const Ogre::Radian& amount) {
    rotate(Ogre::Quaternion(amount, Ogre::Vector3::UNIT_X));
}

void Transform::addChild(Ogre::SceneNode* child) {
    sceneNode->addChild(child);
}

void Transform::removeChild(Ogre::SceneNode* child) {
    sceneNode->removeChild(child);
}

Ogre::SceneNode* Transform::getSceneNode() {
    return sceneNode;
}

const Ogre::Vector3& Transform::getPosition() const {
    return position.getValue();
}

const Ogre::Vector3& Transform::getInterpolatedPosition() const {
    return interpolatedPosition;
}

void Transform::setPosition(const Ogre::Vector3& position) {
    this->position.setValue(position);
}

const Ogre::Quaternion& Transform::getOrientation() const {
    return orientation.getValue();
}

const Ogre::Quaternion& Transform::getInterpolatedOrientation() const {
    return interpolatedOrientation;
}

void Transform::setOrientation(const Ogre::Quaternion& orientation) {
    this->orientation.setValue(orientation);
}
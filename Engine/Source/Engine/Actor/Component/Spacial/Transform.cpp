#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "Transform.h"

ComponentClassDef(Transform)

Transform::Transform(ComponentFactory* factory) :
        SpacialComponent(factory),
        position("position", Ogre::Vector3::ZERO),
        orientation("orientation", Ogre::Quaternion::IDENTITY),
        lastPosition(getPosition()),
        interpolatedPosition(getPosition()),
        lastOrientation(getOrientation()),
        interpolatedOrientation(getOrientation()) {
    addAttribute(&position);
    addAttribute(&orientation);
}

void Transform::enterScene(Scene* scene) {
    SpacialComponent::enterScene(scene);

    sceneNode = scene->getSceneManager()->getRootSceneNode()->createChildSceneNode();

    lastPosition = getPosition();
    lastOrientation = getOrientation();
}

void Transform::leaveScene() {
    sceneNode = nullptr;

    SpacialComponent::leaveScene();
}

void Transform::logicUpdate(Ogre::Real timeStep) {
    lastPosition = getPosition();
    lastOrientation = getOrientation();

    sceneNode->setPosition(interpolatedPosition);
    sceneNode->setOrientation(interpolatedOrientation);
}

void Transform::frameUpdate(Ogre::Real frameDelta) {
    interpolatedPosition = lastPosition + (getPosition() - lastPosition) * frameDelta;

    interpolatedOrientation = interpolate(lastOrientation, getOrientation(), frameDelta);

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

Ogre::Quaternion Transform::interpolate(const Ogre::Quaternion& a, const Ogre::Quaternion& b, Ogre::Real delta) {
    Ogre::Real w1, w2;

    Ogre::Real dotProduct = a.Dot(b);

    Ogre::Quaternion b1;

    if (dotProduct < 0.0f) {
        b1 = -b;
    } else {
        b1 = b;
    }

    dotProduct = a.Dot(b1);

    Ogre::Real theta = (Ogre::Real)acos(dotProduct);
    Ogre::Real sindoubleheta = (Ogre::Real)sin(theta);

    if (sindoubleheta > 0.01f) {
        w1 = Ogre::Math::Sin((1.0f - delta) * theta) / sindoubleheta;
        w2 = Ogre::Math::Sin(delta * theta) / sindoubleheta;
    } else {
        w1 = 1.0f - delta;
        w2 = delta;
    }

    Ogre::Quaternion result(a * w1 + b1 * w2);
    result.normalise();

    return result;
}
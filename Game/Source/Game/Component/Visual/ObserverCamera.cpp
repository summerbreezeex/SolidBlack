#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "ObserverCamera.h"

ObserverCamera::ObserverCamera(ComponentFactory* factory) :
        Camera(factory),
        localMoveDirection(Ogre::Vector3::ZERO),
        localRollDirection(0.0),
        velocity(Ogre::Vector3::ZERO),
        rollVelocity(0.0),
        yawVelocity(0.0),
        pitchVelocity(0.0),
        speedMultiplier(1) {
}

void ObserverCamera::logicUpdate(Ogre::Real timeStep) {
    Camera::logicUpdate(timeStep);

    Ogre::Real speed = speedMultiplier;
    Ogre::Real rollSpeed = 0.5;

    Transform* transform = getTransform();

    velocity += transform->getOrientation() * localMoveDirection.normalisedCopy() * speed * timeStep;
    rollVelocity += localRollDirection * rollSpeed * timeStep;

    transform->translate(velocity);
    transform->roll(Ogre::Radian(rollVelocity));
    transform->yaw(Ogre::Radian(yawVelocity));
    transform->pitch(Ogre::Radian(pitchVelocity));

    velocity *= 0.7;
    rollVelocity *= 0.7;
    yawVelocity *= 0.2;
    pitchVelocity *= 0.2;
}

void ObserverCamera::addLocalMoveDirection(const Ogre::Vector3& direction) {
    localMoveDirection += direction;
}

void ObserverCamera::addLocalRollDirection(Ogre::Real direction) {
    localRollDirection += direction;
}

void ObserverCamera::increaseYawVelocity(Ogre::Real amount) {
    yawVelocity += amount;
}

void ObserverCamera::increasePitchVelocity(Ogre::Real amount) {
    pitchVelocity += amount;
}

void ObserverCamera::increaseSpeed() {
    speedMultiplier *= 2;

    speedMultiplier = std::min(speedMultiplier, 32768);
}

void ObserverCamera::decreaseSpeed() {
    if (speedMultiplier >= 2) {
        speedMultiplier /= 2;
    } else {
        speedMultiplier = 1;
    }
}
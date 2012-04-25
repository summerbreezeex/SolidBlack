#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/Camera.h"

class ObserverCamera :
            public Camera {
public:
    ComponentClass

    ObserverCamera(ComponentFactory* factory);

    void logicUpdate(Ogre::Real timeStep);

    void addLocalMoveDirection(const Ogre::Vector3& direction);
    void addLocalRollDirection(Ogre::Real direction);

    void increaseYawVelocity(Ogre::Real amount);
    void increasePitchVelocity(Ogre::Real amount);

    void increaseSpeed();
    void decreaseSpeed();

private:
    Ogre::Vector3 localMoveDirection;
    Ogre::Real localRollDirection;

    Ogre::Vector3 velocity;

    Ogre::Real rollVelocity, yawVelocity, pitchVelocity;

    int speedMultiplier;
};
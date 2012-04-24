#pragma once

#include <OgreQuaternion.h>
#include <OgreVector3.h>

#include "Engine/Actor/Component/Spacial/SpacialComponent.h"

class Transform :
            public SpacialComponent {
    typedef SpacialComponent Super;
public:
    ComponentClass

    Transform();

    void enterScene(Scene* scene);
    void leaveScene();

    void logicUpdate(Ogre::Real timeStep);
    void frameUpdate(Ogre::Real frameDelta);

    void translate(const Ogre::Vector3& translation);

    void rotate(const Ogre::Vector3& axis, const Ogre::Radian& angle);
    void rotate(Ogre::Quaternion quaternion);

    void roll(const Ogre::Radian& amount);
    void yaw(const Ogre::Radian& amount);
    void pitch(const Ogre::Radian& amount);

    void addChild(Ogre::SceneNode* child);
    void removeChild(Ogre::SceneNode* child);

    Ogre::SceneNode* getSceneNode();

    const Ogre::Vector3& getPosition() const;
    const Ogre::Vector3& getInterpolatedPosition() const;
    void setPosition(const Ogre::Vector3& position);

    const Ogre::Quaternion& getOrientation() const;
    const Ogre::Quaternion& getInterpolatedOrientation() const;
    void setOrientation(const Ogre::Quaternion& orientation);

private:
    ComponentAttribute<Ogre::Vector3> position;
    ComponentAttribute<Ogre::Quaternion> orientation;

    Ogre::Vector3 lastPosition, interpolatedPosition;
    Ogre::Quaternion lastOrientation, interpolatedOrientation;

    Ogre::SceneNode* sceneNode;
};
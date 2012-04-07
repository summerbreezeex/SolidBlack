#pragma once

#include <OgreTimer.h>
#include <OgreVector3.h>

#include "Engine/Actor/Component/Logical/LogicalComponent.h"

class Transform;

class ProjectileLogic :
            public LogicalComponent {
    typedef LogicalComponent Super;
public:
    static std::string typeName;

    ProjectileLogic();

    void attachToActor(Actor* actor);
    void detachFromActor();

    void logicUpdate(Ogre::Real timeStep);

private:
    Attribute<Ogre::Vector3> velocity;

    Transform* transform;

    Ogre::Timer timer;
};
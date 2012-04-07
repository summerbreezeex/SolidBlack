#pragma once

#include "Engine/Actor/Component/Logical/LogicalComponent.h"

class Transform;

class TestLogic :
            public LogicalComponent {
    typedef LogicalComponent Super;
public:
    static std::string typeName;

    TestLogic();

    void attachToActor(Actor* actor);
    void detachFromActor();

    void logicUpdate(Ogre::Real timeStep);

private:
    Transform* transform;
};
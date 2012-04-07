#pragma once

#include <OgreQuaternion.h>
#include <OgreVector3.h>

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "Engine/StlCommon.h"

class RigidBody;

class Physics {
public:
    Physics();

    void logicUpdate(Ogre::Real timeStep);

    void addRigidBody(RigidBody* rigidBody);
    void removeRigidBody(RigidBody* rigidBody);

private:
    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> broadphase;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
    std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
    std::unique_ptr<btGhostPairCallback> ghostPairCallback;

    std::vector<RigidBody*> rigidBodies;
};
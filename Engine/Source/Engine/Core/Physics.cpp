#include <BtOgreGP.h>

#include "Engine/Actor/Component/Physical/RigidBody.h"

#include "Physics.h"

Physics::Physics() :
        collisionConfiguration(new btDefaultCollisionConfiguration()),
        dispatcher(new btCollisionDispatcher(collisionConfiguration.get())),
        broadphase(new btDbvtBroadphase()),
        solver(new btSequentialImpulseConstraintSolver()),
        dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get())),
        ghostPairCallback(new btGhostPairCallback()) {
    dynamicsWorld->getPairCache()->setInternalGhostPairCallback(ghostPairCallback.get());
}

void Physics::logicUpdate(Ogre::Real timeStep) {
    int subStepCount = 4;
    Ogre::Real subStepDenominator = subStepCount;

    for (int i = 0; i < subStepCount; ++i) {
        dynamicsWorld->stepSimulation(timeStep / subStepDenominator, 0);
    }
}

void Physics::addRigidBody(RigidBody* rigidBody) {
    dynamicsWorld->addRigidBody(rigidBody->rigidBody);
}

void Physics::removeRigidBody(RigidBody* rigidBody) {
    dynamicsWorld->removeRigidBody(rigidBody->rigidBody);
}
#include <OgreMesh.h>

#include <btBulletDynamicsCommon.h>

#include <BtOgreGP.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Actor/Component/Visual/Mesh.h"

#include "RigidBody.h"

std::string RigidBody::typeName = "RigidBody";

RigidBody::RigidBody() :
        mass("mass", 0.0),
        transform(nullptr),
        mesh(nullptr),
        shape(nullptr),
        rigidBody(nullptr),
        initialised(false) {
    addImplementedTypeName(typeName);
    addAttribute(&mass);
}

void RigidBody::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    transform = actor->findComponentOfType<Transform>();
    mesh = actor->findComponentOfType<Mesh>();
}

void RigidBody::detachFromActor() {
    transform = nullptr;
    mesh = nullptr;

    Super::detachFromActor();
}

void RigidBody::enterScene(Scene* scene) {
    Super::enterScene(scene);

    if (mesh) {
        initialise();
    }
}

void RigidBody::leaveScene() {
    if (initialised) {
        deinitialise();
    }

    Super::leaveScene();
}

void RigidBody::logicUpdate(Ogre::Real timeStep) {
    if (initialised && transform) {
        transform->setPosition(BtOgre::Convert::toOgre(rigidBody->getWorldTransform().getOrigin()));
        transform->setOrientation(BtOgre::Convert::toOgre(rigidBody->getWorldTransform().getRotation()));
    }
}

Ogre::Real RigidBody::getMass() const {
    return mass.getValue();
}

void RigidBody::setMass(Ogre::Real mass) {
    this->mass.setValue(mass);
}

void RigidBody::initialise() {
    initialised = true;

    btVector3 localInertia(0.0, 0.0, 0.0);

    if (getMass() > 0.0) {
        BtOgre::StaticMeshToShapeConverter converter(mesh->getEntity());
        shape = converter.createConvex();

        shape->calculateLocalInertia(getMass(), localInertia);
    } else {
        BtOgre::StaticMeshToShapeConverter converter(mesh->getEntity());
        shape = converter.createTrimesh();
    }

    btRigidBody::btRigidBodyConstructionInfo info(getMass(), 0, shape, localInertia);
    rigidBody = new btRigidBody(info);

    if (getMass() <= 0.0) {
        rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
        rigidBody->setFriction(1.0);
    }

    rigidBody->setRestitution(0.0);

    btTransform transformation;
    transformation.setOrigin(BtOgre::Convert::toBullet(transform->getPosition()));
    transformation.setRotation(BtOgre::Convert::toBullet(transform->getOrientation()));
    rigidBody->setWorldTransform(transformation);

    getScene()->getPhysics()->addRigidBody(this);
}

void RigidBody::deinitialise() {
    getScene()->getPhysics()->removeRigidBody(this);

    delete shape;
    delete rigidBody;

    initialised = false;
}
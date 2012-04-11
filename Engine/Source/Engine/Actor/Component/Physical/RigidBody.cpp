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
        linearVelocity("linearVelocity", Ogre::Vector3::ZERO),
        angularVelocity("angularVelocity", Ogre::Vector3::ZERO),
        shape(nullptr),
        rigidBody(nullptr),
        initialized(false) {
    addImplementedTypeName(typeName);
    addAttribute(&mass);
    addAttribute(&linearVelocity);
    addAttribute(&angularVelocity);
    addDependency(&transform);
    addDependency(&mesh);
}

void RigidBody::enterScene(Scene* scene) {
    Super::enterScene(scene);

    if (mesh) {
        initialize();
    }
}

void RigidBody::leaveScene() {
    if (initialized) {
        deinitialize();
    }

    Super::leaveScene();
}

void RigidBody::logicUpdate(Ogre::Real timeStep) {
    if (initialized && transform) {
        (*transform)->setPosition(BtOgre::Convert::toOgre(rigidBody->getWorldTransform().getOrigin()));
        (*transform)->setOrientation(BtOgre::Convert::toOgre(rigidBody->getWorldTransform().getRotation()));
    }
}

Ogre::Real RigidBody::getMass() const {
    return *mass;
}

void RigidBody::setMass(Ogre::Real mass) {
    *this->mass = mass;
}

const Ogre::Vector3& RigidBody::getLinearVelocity() const {
    return *linearVelocity;
}

const Ogre::Vector3& RigidBody::getAngularVelocity() const {
    return *angularVelocity;
}

void RigidBody::initialize() {
    initialized = true;

    btVector3 localInertia(0.0, 0.0, 0.0);

    if (getMass() > 0.0) {
        BtOgre::StaticMeshToShapeConverter converter((*mesh)->getEntity());
        shape = converter.createConvex();

        shape->calculateLocalInertia(getMass(), localInertia);
    } else {
        BtOgre::StaticMeshToShapeConverter converter((*mesh)->getEntity());
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
    transformation.setOrigin(BtOgre::Convert::toBullet((*transform)->getPosition()));
    transformation.setRotation(BtOgre::Convert::toBullet((*transform)->getOrientation()));
    rigidBody->setWorldTransform(transformation);

    rigidBody->setLinearVelocity(BtOgre::Convert::toBullet(getLinearVelocity()));
    rigidBody->setAngularVelocity(BtOgre::Convert::toBullet(getAngularVelocity()));

    getScene()->getPhysics()->addRigidBody(this);
}

void RigidBody::deinitialize() {
    getScene()->getPhysics()->removeRigidBody(this);

    delete shape;
    delete rigidBody;

    initialized = false;
}
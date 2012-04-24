#include <OgreMesh.h>

#include <btBulletDynamicsCommon.h>

#include <BtOgreGP.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Actor/Component/Visual/Mesh.h"

#include "RigidBody.h"

ComponentClassDef(RigidBody)

RigidBody::RigidBody() :
        mass("mass", 0.0),
        linearVelocity("linearVelocity", Ogre::Vector3::ZERO),
        angularVelocity("angularVelocity", Ogre::Vector3::ZERO),
        shape(nullptr),
        rigidBody(nullptr),
        initialized(false) {
    getTypeData()->setDerivedTypeName(typeName);
    addAttribute(&mass);
    addAttribute(&linearVelocity);
    addAttribute(&angularVelocity);
    addDependency(&transform);
}

void RigidBody::enterScene(Scene* scene) {
    Super::enterScene(scene);
    
    initializeRigidBody();
}

void RigidBody::leaveScene() {
    if (initialized) {
        deinitializeRigidBody();
    }

    Super::leaveScene();
}

void RigidBody::logicUpdate(Ogre::Real timeStep) {
    if (initialized) {
        auto transformComponent = transform.getComponent();
        transformComponent->setPosition(BtOgre::Convert::toOgre(rigidBody->getWorldTransform().getOrigin()));
        transformComponent->setOrientation(BtOgre::Convert::toOgre(rigidBody->getWorldTransform().getRotation()));
    }
}

Ogre::Real RigidBody::getMass() const {
    return mass.getValue();
}

void RigidBody::setMass(Ogre::Real mass) {
    this->mass.setValue(mass);
}

const Ogre::Vector3& RigidBody::getLinearVelocity() const {
    return linearVelocity.getValue();
}

const Ogre::Vector3& RigidBody::getAngularVelocity() const {
    return angularVelocity.getValue();
}

void RigidBody::initializeRigidBody() {
    initialized = true;

    btVector3 localInertia(0.0, 0.0, 0.0);

    auto transformComponent = transform.getComponent();

    if (getMass() > 0.0) {
        BtOgre::StaticMeshToShapeConverter converter;

        auto meshComponents = getActor()->findComponentsOfType<Mesh>();
        foreach (meshComponent, meshComponents) {
            converter.addEntity((*meshComponent)->getEntity());
        }

        shape = converter.createConvex();

        shape->calculateLocalInertia(getMass(), localInertia);
    } else {
        BtOgre::StaticMeshToShapeConverter converter;

        auto meshComponents = getActor()->findComponentsOfType<Mesh>();
        foreach (meshComponent, meshComponents) {
            converter.addEntity((*meshComponent)->getEntity());
        }

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
    transformation.setOrigin(BtOgre::Convert::toBullet(transformComponent->getPosition()));
    transformation.setRotation(BtOgre::Convert::toBullet(transformComponent->getOrientation()));
    rigidBody->setWorldTransform(transformation);

    rigidBody->setLinearVelocity(BtOgre::Convert::toBullet(getLinearVelocity()));
    rigidBody->setAngularVelocity(BtOgre::Convert::toBullet(getAngularVelocity()));

    getScene()->getPhysics()->addRigidBody(this);
}

void RigidBody::deinitializeRigidBody() {
    getScene()->getPhysics()->removeRigidBody(this);

    delete shape;
    delete rigidBody;

    initialized = false;
}
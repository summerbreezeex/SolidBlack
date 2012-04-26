#include <OgreMesh.h>

#include <btBulletDynamicsCommon.h>

#include <BtOgreGP.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Actor/Component/Visual/Mesh.h"

#include "RigidBody.h"

RigidBody::RigidBody(ComponentFactory* factory) :
        PhysicalComponent(factory),
        mass("mass", 0.0),
        linearVelocity("linearVelocity", Ogre::Vector3::ZERO),
        angularVelocity("angularVelocity", Ogre::Vector3::ZERO),
        collisionShape("collisionShape", "ConvexHull"),
        physics(nullptr),
        shape(nullptr),
        rigidBody(nullptr),
        initialized(false) {
    addAttribute(&mass);
    addAttribute(&linearVelocity);
    addAttribute(&angularVelocity);
    addAttribute(&collisionShape);
    addDependency(&transform);
}

void RigidBody::enterScene(Scene* scene) {
    PhysicalComponent::enterScene(scene);
    
    physics = scene->getPhysics();
    initializeRigidBody();
}

void RigidBody::leaveScene() {
    if (initialized) {
        deinitializeRigidBody();
    }
    physics = nullptr;

    PhysicalComponent::leaveScene();
}

void RigidBody::logicUpdate(Ogre::Real timeStep) {
    PhysicalComponent::logicUpdate(timeStep);

    if (!initialized) {
        return;
    }

    const btTransform& worldTransform = rigidBody->getWorldTransform();

    auto transformComponent = transform.getComponent();
    transformComponent->setPosition(BtOgre::Convert::toOgre(worldTransform.getOrigin()));
    transformComponent->setOrientation(BtOgre::Convert::toOgre(worldTransform.getRotation()));
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

    BtOgre::StaticMeshToShapeConverter converter;
    auto meshComponents = getActor()->findComponentsOfType<Mesh>();
    foreach (meshComponent, meshComponents) {
        converter.addEntity((*meshComponent)->getEntity());
    }

    if (collisionShape.getValue() == "ConvexHull") {
        shape = converter.createConvex();
    } else if (collisionShape.getValue() == "TriangleMesh") {
        shape = converter.createTrimesh();
    } else if (collisionShape.getValue() == "Box") {
        shape = converter.createBox();
    } else if (collisionShape.getValue() == "Sphere") {
        shape = converter.createSphere();
    } else {
        throw std::runtime_error("Unknown collision shape '" + collisionShape.getValue() + "'");
    }

    btVector3 localInertia(0.0, 0.0, 0.0);
    if (getMass() > 0.0) {
        shape->calculateLocalInertia(getMass(), localInertia);
    }

    btRigidBody::btRigidBodyConstructionInfo info(getMass(), 0, shape, localInertia);
    rigidBody = new btRigidBody(info);

    if (getMass() <= 0.0) {
        rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
        rigidBody->setFriction(1.0);
    }

    auto transformComponent = transform.getComponent();

    btTransform worldTransform;
    worldTransform.setOrigin(BtOgre::Convert::toBullet(transformComponent->getPosition()));
    worldTransform.setRotation(BtOgre::Convert::toBullet(transformComponent->getOrientation()));
    rigidBody->setWorldTransform(worldTransform);

    rigidBody->setLinearVelocity(BtOgre::Convert::toBullet(getLinearVelocity()));
    rigidBody->setAngularVelocity(BtOgre::Convert::toBullet(getAngularVelocity()));

    physics->addRigidBody(this);
}

void RigidBody::deinitializeRigidBody() {
    physics->removeRigidBody(this);

    delete shape;
    delete rigidBody;

    initialized = false;
}
#pragma once

#include <OgrePrerequisites.h>
#include <OgreVector3.h>

#include "Engine/Actor/Component/Physical/PhysicalComponent.h"

class btCollisionShape;
class btRigidBody;

class Transform;
class Mesh;

class RigidBody :
            public PhysicalComponent {
    typedef PhysicalComponent Super;
    friend class Physics;
public:
    ComponentClass

    RigidBody();

    void enterScene(Scene* scene);
    void leaveScene();

    void logicUpdate(Ogre::Real timeStep);

    Ogre::Real getMass() const;
    void setMass(Ogre::Real mass);

    const Ogre::Vector3& getLinearVelocity() const;
    const Ogre::Vector3& getAngularVelocity() const;

private:
    void initializeRigidBody();
    void deinitializeRigidBody();

    ComponentAttribute<Ogre::Real> mass;
    ComponentAttribute<Ogre::Vector3> linearVelocity;
    ComponentAttribute<Ogre::Vector3> angularVelocity;

    ComponentDependency<Transform> transform;

    btCollisionShape* shape;
    btRigidBody* rigidBody;

    bool initialized;
};
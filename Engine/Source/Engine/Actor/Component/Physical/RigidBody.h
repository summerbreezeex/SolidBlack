#pragma once

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
    static std::string typeName;

    RigidBody();

    void attachToActor(Actor* actor);
    void detachFromActor();
    void enterScene(Scene* scene);
    void leaveScene();

    void logicUpdate(Ogre::Real timeStep);

    Ogre::Real getMass() const;
    void setMass(Ogre::Real mass);

private:
    void initialise();
    void deinitialise();

    Attribute<Ogre::Real> mass;

    Transform* transform;
    Mesh* mesh;

    btCollisionShape* shape;
    btRigidBody* rigidBody;

    bool initialised;
};
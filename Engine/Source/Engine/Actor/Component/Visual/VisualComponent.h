#pragma once

#include <OgrePrerequisites.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

#include "Engine/Actor/Component/Component.h"

class Transform;

class VisualComponent :
            public Component {
    typedef Component Super;
public:
    static std::string typeName;

    VisualComponent();
    virtual ~VisualComponent() { }

    void attachToActor(Actor* actor);
    void detachFromActor();
    void enterScene(Scene* scene);
    void leaveScene();

    const Ogre::Vector3& getLocalPosition() const;
    const Ogre::Quaternion& getLocalOrientation() const;

    Transform* getTransform();
    Ogre::SceneNode* getSceneNode();

private:
    Attribute<Ogre::Vector3> localPosition;
    Attribute<Ogre::Quaternion> localOrientation;

    Transform* transform;

    Ogre::SceneNode* sceneNode;
};
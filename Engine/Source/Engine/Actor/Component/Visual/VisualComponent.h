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

    void enterScene(Scene* scene);
    void leaveScene();

    const Ogre::Vector3& getLocalPosition() const;
    const Ogre::Quaternion& getLocalOrientation() const;

    Transform* getTransform();
    const Transform* getTransform() const;

    Ogre::SceneNode* getSceneNode();
    const Ogre::SceneNode* getSceneNode() const;

private:
    ComponentAttribute<Ogre::Vector3> localPosition;
    ComponentAttribute<Ogre::Quaternion> localOrientation;

    ComponentDependency<Transform> transform;

    Ogre::SceneNode* sceneNode;
};
#include <OgreSceneManager.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "VisualComponent.h"

std::string VisualComponent::typeName = "VisualComponent";

VisualComponent::VisualComponent() :
        localPosition("localPosition", Ogre::Vector3::ZERO),
        localOrientation("localOrientation", Ogre::Quaternion::IDENTITY),
        sceneNode(nullptr) {
    setFamily("Visual");
    addImplementedTypeName(typeName);
    addAttribute(&localPosition);
    addAttribute(&localOrientation);
    addDependency(&transform);
}

void VisualComponent::enterScene(Scene* scene) {
    Super::enterScene(scene);

    if (transform) {
        sceneNode = (*transform)->getSceneNode()->createChildSceneNode();

        sceneNode->setPosition(getLocalPosition());
        sceneNode->setOrientation(getLocalOrientation());
    }
}

void VisualComponent::leaveScene() {
    if (sceneNode) {
        if (sceneNode->numAttachedObjects() > 0) {
            getScene()->logWarning("Visual component in actor '" + getActor()->getName() + "' has residual attached objects.");
        }

        if (sceneNode->numChildren() > 0) {
            getScene()->logWarning("Visual component in actor '" + getActor()->getName() + "' has residual attached child nodes.");
        }

        getScene()->getSceneManager()->destroySceneNode(sceneNode);
        sceneNode = nullptr;
    }

    Super::leaveScene();
}

const Ogre::Vector3& VisualComponent::getLocalPosition() const {
    return *localPosition;
}

const Ogre::Quaternion& VisualComponent::getLocalOrientation() const {
    return *localOrientation;
}

Transform* VisualComponent::getTransform() {
    return *transform;
}

const Transform* VisualComponent::getTransform() const {
    return *transform;
}

Ogre::SceneNode* VisualComponent::getSceneNode() {
    return sceneNode;
}

const Ogre::SceneNode* VisualComponent::getSceneNode() const {
    return sceneNode;
}
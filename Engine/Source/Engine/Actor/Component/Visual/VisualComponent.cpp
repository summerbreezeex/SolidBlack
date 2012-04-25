#include <OgreSceneManager.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "VisualComponent.h"

ComponentClassDef(VisualComponent)

VisualComponent::VisualComponent(ComponentFactory* factory) :
        Component(factory),
        localPosition("localPosition", Ogre::Vector3::ZERO),
        localOrientation("localOrientation", Ogre::Quaternion::IDENTITY),
        sceneNode(nullptr) {
    addAttribute(&localPosition);
    addAttribute(&localOrientation);
    addDependency(&transform);
}

void VisualComponent::enterScene(Scene* scene) {
    Component::enterScene(scene);

    auto transformComponent = transform.getComponent();

    sceneNode = transformComponent->getSceneNode()->createChildSceneNode();

    sceneNode->setPosition(getLocalPosition());
    sceneNode->setOrientation(getLocalOrientation());
}

void VisualComponent::leaveScene() {
    if (sceneNode->numAttachedObjects() > 0) {
        getScene()->logWarning("Visual component in actor '" + getActor()->getName() + "' has residual attached objects.");
    }

    if (sceneNode->numChildren() > 0) {
        getScene()->logWarning("Visual component in actor '" + getActor()->getName() + "' has residual attached child nodes.");
    }

    getScene()->getSceneManager()->destroySceneNode(sceneNode);
    sceneNode = nullptr;

    Component::leaveScene();
}

const Ogre::Vector3& VisualComponent::getLocalPosition() const {
    return localPosition.getValue();
}

const Ogre::Quaternion& VisualComponent::getLocalOrientation() const {
    return localOrientation.getValue();
}

Transform* VisualComponent::getTransform() {
    return transform.getComponent();
}

const Transform* VisualComponent::getTransform() const {
    return transform.getComponent();
}

Ogre::SceneNode* VisualComponent::getSceneNode() {
    return sceneNode;
}

const Ogre::SceneNode* VisualComponent::getSceneNode() const {
    return sceneNode;
}
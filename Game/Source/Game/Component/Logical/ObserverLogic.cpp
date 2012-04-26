#include <OgreVector4.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Actor/Component/Visual/Light/SpotLight.h"

#include "Game/Component/Visual/ObserverCamera.h"

#include "ObserverLogic.h"

ObserverLogic::ObserverLogic(ComponentFactory* factory) :
        LogicalComponent(factory) {
    addDependency(&observerCamera);
}

void ObserverLogic::debugAction1() {
    if (observerCamera) {
        auto observerCameraComponent = observerCamera.getComponent();

        Scene* scene = getScene();
        ComponentFactory* factory = scene->getComponentFactory();

        Actor* actor = new Actor("spotLight");

        Component* transform = factory->createComponent("Transform");
        transform->setAttributeValue("position", observerCameraComponent->getTransform()->getPosition());
        transform->setAttributeValue("orientation", observerCameraComponent->getTransform()->getOrientation());
        actor->addComponent(transform);

        Component* spotLight = factory->createComponent("SpotLight");
        spotLight->setAttributeValue("attenuation", Ogre::Vector4(20.0, 0.5, 0.0, 0.3));
        actor->addComponent(spotLight);

        actor->attachComponents();

        scene->addActor(actor);
    }
}

void ObserverLogic::debugAction2() {
    if (observerCamera) {
        auto observerCameraComponent = observerCamera.getComponent();

        Scene* scene = getScene();
        ComponentFactory* factory = scene->getComponentFactory();

        Actor* actor = new Actor("observerProjectile");

        Component* transform = factory->createComponent("Transform");
        transform->setAttributeValue("position", observerCameraComponent->getTransform()->getPosition());
        transform->setAttributeValue("orientation", observerCameraComponent->getTransform()->getOrientation());
        actor->addComponent(transform);

        Component* mesh = factory->createComponent("Mesh");
        mesh->setAttributeValue("meshName", std::string("MetalCrate.mesh"));
        actor->addComponent(mesh);

        Component* rigidBody = factory->createComponent("RigidBody");
        rigidBody->setAttributeValue("mass", 1000.0);
        rigidBody->setAttributeValue("linearVelocity", observerCameraComponent->getDirection() * 10.0);
        rigidBody->setAttributeValue("collisionShape", std::string("Box"));
        actor->addComponent(rigidBody);

        actor->attachComponents();

        scene->addActor(actor);
    }
}

void ObserverLogic::debugAction3() {
    if (observerCamera) {
        SpotLight* spotLight = getActor()->findComponentOfType<SpotLight>();

        if (spotLight) {
            spotLight->setEnabled(!spotLight->isEnabled());
        }
    }
}
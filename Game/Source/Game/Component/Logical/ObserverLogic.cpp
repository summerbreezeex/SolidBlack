#include <OgreVector4.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Actor/Component/Visual/Light/SpotLight.h"

#include "Game/Component/Visual/ObserverCamera.h"

#include "ObserverLogic.h"

std::string ObserverLogic::typeName = "ObserverLogic";

ObserverLogic::ObserverLogic() {
    addImplementedTypeName(typeName);
    addDependency(&observerCamera);
}

void ObserverLogic::debugAction1() {
    if (observerCamera) {
        Scene* scene = getScene();
        ComponentFactory* factory = scene->getComponentFactory();

        Actor* actor = new Actor("spotLight");

        Component* transform = factory->createComponent("Transform");
        transform->setAttributeValue("position", (*observerCamera)->getTransform()->getPosition());
        transform->setAttributeValue("orientation", (*observerCamera)->getTransform()->getOrientation());
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
        Scene* scene = getScene();
        ComponentFactory* factory = scene->getComponentFactory();

        Actor* actor = new Actor("observerProjectile");

        Component* transform = factory->createComponent("Transform");
        transform->setAttributeValue("position", (*observerCamera)->getTransform()->getPosition());
        transform->setAttributeValue("orientation", (*observerCamera)->getTransform()->getOrientation());
        actor->addComponent(transform);

        Component* mesh = factory->createComponent("Mesh");
        mesh->setAttributeValue("meshName", std::string("MetalCrate.mesh"));
        actor->addComponent(mesh);

        Component* rigidBody = factory->createComponent("RigidBody");
        rigidBody->setAttributeValue("mass", 100.0);
        rigidBody->setAttributeValue("linearVelocity", (*observerCamera)->getDirection() * 10.0);
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
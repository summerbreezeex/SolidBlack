#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "ProjectileLogic.h"

std::string ProjectileLogic::typeName = "ProjectileLogic";

ProjectileLogic::ProjectileLogic() :
        velocity("velocity", Ogre::Vector3::ZERO),
        transform(nullptr) {
    addImplementedTypeName(typeName);
    addAttribute(&velocity);
}

void ProjectileLogic::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    transform = actor->findComponentOfType<Transform>();

    timer.reset();
}

void ProjectileLogic::detachFromActor() {
    transform = nullptr;

    Super::detachFromActor();
}

void ProjectileLogic::logicUpdate(Ogre::Real timeStep) {
    if (transform) {
        transform->translate(velocity.getValue() * timeStep);
    }

    if (timer.getMilliseconds() > 5000) {
        //getActor()->kill();
    }
}
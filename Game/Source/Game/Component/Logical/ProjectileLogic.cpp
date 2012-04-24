#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "ProjectileLogic.h"

ComponentClassDef(ProjectileLogic)

ProjectileLogic::ProjectileLogic() :
        velocity("velocity", Ogre::Vector3::ZERO) {
    getTypeData()->setDerivedTypeName(typeName);
    addAttribute(&velocity);
    addDependency(&transform);
}

void ProjectileLogic::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    timer.reset();
}

void ProjectileLogic::logicUpdate(Ogre::Real timeStep) {
    auto transformComponent = transform.getComponent();
    transformComponent->translate(velocity.getValue() * timeStep);

    if (timer.getMilliseconds() > 5000) {
        //getActor()->kill();
    }
}
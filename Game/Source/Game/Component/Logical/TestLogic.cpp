#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/Spacial/Transform.h"

#include "TestLogic.h"

std::string TestLogic::typeName = "TestLogic";

TestLogic::TestLogic() :
        transform(nullptr) {
    addImplementedTypeName(typeName);
}

void TestLogic::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    transform = actor->findComponentOfType<Transform>();
}

void TestLogic::detachFromActor() {
    transform = nullptr;

    Super::detachFromActor();
}

void TestLogic::logicUpdate(Ogre::Real timeStep) {
    if (transform) {
        //transform->translate(Ogre::Vector3(10.0 * timeStep, 0.0, 0.0));
        //transform->rotate(Ogre::Vector3(0.0, 1.0, 0.0), Ogre::Radian(3.1415 * 0.5 * timeStep));
    }
}
#include "Engine/Actor/Component/ComponentFactory.h"

#include "Game/Component/Input/ObserverInput.h"
#include "Game/Component/Logical/ObserverLogic.h"
#include "Game/Component/Logical/ProjectileLogic.h"
#include "Game/Component/Logical/TestLogic.h"
#include "Game/Component/Visual/ObserverCamera.h"
#include "Game/Component/Visual/PlanetarySurface.h"

#include "SolidBlackComponentModule.h"

void SolidBlackComponentModule::registerComponents(ComponentFactory* factory) {
    // Input
    factory->registerComponent<ObserverInput>();

    // Logical
    factory->registerComponent<ObserverLogic>();
    factory->registerComponent<ProjectileLogic>();
    factory->registerComponent<TestLogic>();

    // Visual
    factory->registerComponent<ObserverCamera>();
    factory->registerComponent<PlanetarySurface>();
}

void SolidBlackComponentModule::registerCode(ScriptInterpreter* interpreter) {

}
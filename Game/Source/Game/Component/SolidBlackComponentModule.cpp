#include "Engine/Actor/Component/ComponentFactory.h"

#include "Game/Component/Input/ObserverInput.h"
#include "Game/Component/Logical/ObserverLogic.h"
#include "Game/Component/Visual/ObserverCamera.h"
#include "Game/Component/Visual/PlanetarySurface.h"

#include "SolidBlackComponentModule.h"

void SolidBlackComponentModule::registerComponents(ComponentFactory* factory) {
    factory->registerComponent<ObserverInput, InputComponent>();

    factory->registerComponent<ObserverLogic, LogicalComponent>();

    factory->registerComponent<ObserverCamera, Camera>();
    factory->registerComponent<PlanetarySurface, VisualComponent>();
}

void SolidBlackComponentModule::registerCode(ScriptInterpreter* interpreter) {
}
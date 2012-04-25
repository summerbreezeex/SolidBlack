#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Actor/Component/Input/InputComponent.h"
#include "Engine/Actor/Component/Logical/Script.h"
#include "Engine/Actor/Component/Physical/RigidBody.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Actor/Component/Visual/Light/DirectionalLight.h"
#include "Engine/Actor/Component/Visual/Light/PointLight.h"
#include "Engine/Actor/Component/Visual/Light/SpotLight.h"
#include "Engine/Actor/Component/Visual/Camera.h"
#include "Engine/Actor/Component/Visual/Mesh.h"
#include "Engine/Actor/Component/Visual/SkyBox.h"
#include "Engine/Scripting/ScriptInterpreter.h"

#include "CoreComponentModule.h"

void CoreComponentModule::registerComponents(ComponentFactory* factory) {
    // Input
    factory->registerBaseComponent<InputComponent>(ComponentFamily::Input);

    // Logical
    factory->registerBaseComponent<LogicalComponent>(ComponentFamily::Logical);
    factory->registerComponent<Script, LogicalComponent>();

    // Physical
    factory->registerBaseComponent<PhysicalComponent>(ComponentFamily::Physical);
    factory->registerComponent<RigidBody, PhysicalComponent>();

    // Spacial
    factory->registerBaseComponent<SpacialComponent>(ComponentFamily::Spacial);
    factory->registerComponent<Transform, SpacialComponent>();

    // Visual
    factory->registerBaseComponent<VisualComponent>(ComponentFamily::Visual);
    factory->registerComponent<Camera, VisualComponent>();
    factory->registerComponent<Mesh, VisualComponent>();
    factory->registerComponent<SkyBox, VisualComponent>();

    // Visual -> Light
    factory->registerAbstractComponent<Light, VisualComponent>();
    factory->registerComponent<DirectionalLight, Light>();
    factory->registerComponent<PointLight, Light>();
    factory->registerComponent<SpotLight, Light>();    
}

void CoreComponentModule::registerCode(ScriptInterpreter* interpreter) {
    using namespace luabind;

    module(interpreter->getLuaState()) [
        class_<Script, Component>("ScriptWrapper"),

        class_<Transform, Component>("Transform")
            .def("rotate", (void(Transform::*)(const Ogre::Vector3&, const Ogre::Radian&))&Transform::rotate),
        class_<ComponentDependency<Transform>, ComponentDependencyBase>("TransformDependency")
            .def(constructor<>())
            .property("component", &ComponentDependency<Transform>::getBaseComponent)
    ];
}
#include "Engine/Actor/Component/ComponentFactory.h"
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
    // Logical
    factory->registerComponent<Script>();

    // Physical
    factory->registerComponent<RigidBody>();

    // Spacial
    factory->registerComponent<Transform>();

    // Visual/Light
    factory->registerComponent<DirectionalLight>();
    factory->registerComponent<PointLight>();
    factory->registerComponent<SpotLight>();

    // Visual
    factory->registerComponent<Camera>();
    factory->registerComponent<Mesh>();
    factory->registerComponent<SkyBox>();
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
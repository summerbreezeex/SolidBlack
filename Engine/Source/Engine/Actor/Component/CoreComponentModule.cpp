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
    factory->registerBaseComponent<InputComponent>(ComponentFamily::Input);

    factory->registerBaseComponent<LogicalComponent>(ComponentFamily::Logical);
    factory->registerComponent<Script, LogicalComponent>();

    factory->registerBaseComponent<PhysicalComponent>(ComponentFamily::Physical);
    factory->registerComponent<RigidBody, PhysicalComponent>();

    factory->registerBaseComponent<SpacialComponent>(ComponentFamily::Spacial);
    factory->registerComponent<Transform, SpacialComponent>();

    factory->registerBaseComponent<VisualComponent>(ComponentFamily::Visual);
    factory->registerComponent<Camera, VisualComponent>();
    factory->registerComponent<Mesh, VisualComponent>();
    factory->registerComponent<SkyBox, VisualComponent>();
    factory->registerAbstractComponent<Light, VisualComponent>();
    factory->registerComponent<DirectionalLight, Light>();
    factory->registerComponent<PointLight, Light>();
    factory->registerComponent<SpotLight, Light>();    
}

void CoreComponentModule::registerCode(ScriptInterpreter* interpreter) {
    using namespace luabind;

    module(interpreter->getLuaState()) [
        // LogicalComponent
        class_<LogicalComponent, Component>("LogicalComponent"),

        // ScriptWrapper
        class_<Script, LogicalComponent>("ScriptWrapper"),

        // SpacialComponent
        class_<SpacialComponent, Component>("SpacialComponent"),

        // Transform
        class_<Transform, SpacialComponent>("Transform")
            .def("rotate", (void(Transform::*)(const Ogre::Vector3&, const Ogre::Radian&))&Transform::rotate),
        class_<ComponentDependency<Transform>, ComponentDependencyBase>("TransformDependency")
            .def(constructor<>()),

        // VisualComponent
        class_<VisualComponent, Component>("VisualComponent"),

        // Light
        class_<Light, VisualComponent>("Light")
            .property("diffuseColour", (Ogre::ColourValue&(Light::*)())&Light::getDiffuseColour, &Light::setDiffuseColour)
            .property("specularColour", (Ogre::ColourValue&(Light::*)())&Light::getSpecularColour, &Light::setSpecularColour)
            .property("enabled", &Light::isEnabled, &Light::setEnabled),
        class_<ComponentDependency<Light>, ComponentDependencyBase>("LightDependency")
            .def(constructor<>()),

        // PointLight
        class_<PointLight, Light>("PointLight"),
        class_<ComponentDependency<PointLight>, ComponentDependencyBase>("PointLightDependency")
            .def(constructor<>())
    ];
}
#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Actor/Component/Physical/RigidBody.h"
#include "Engine/Actor/Component/Visual/Light/DirectionalLight.h"
#include "Engine/Actor/Component/Visual/Light/PointLight.h"
#include "Engine/Actor/Component/Visual/Light/SpotLight.h"
#include "Engine/Actor/Component/Visual/Camera.h"
#include "Engine/Actor/Component/Visual/Mesh.h"
#include "Engine/Actor/Component/Visual/SkyBox.h"

#include "DefaultComponentModule.h"

void DefaultComponentModule::registerComponents(ComponentFactory* factory) {
    // Spacial
    factory->registerComponent<Transform>();

    // Physical
    factory->registerComponent<RigidBody>();

    // Visual/Light
    factory->registerComponent<DirectionalLight>();
    factory->registerComponent<PointLight>();
    factory->registerComponent<SpotLight>();

    // Visual
    factory->registerComponent<Camera>();
    factory->registerComponent<Mesh>();
    factory->registerComponent<SkyBox>();
}
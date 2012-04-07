#pragma once

#include "Engine/Actor/Component/ComponentModule.h"

// Physical
class RigidBody;

// Spacial
class Transform;

// Visual
class Camera;
class DirectionalLight;
class Mesh;
class PointLight;
class SkyBox;
class SpotLight;

class DefaultComponentModule :
            public ComponentModule {
public:
    void registerComponents(ComponentFactory* factory);
};
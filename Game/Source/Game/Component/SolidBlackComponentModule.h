#pragma once

#include "Engine/Actor/Component/ComponentModule.h"

// Input
class ObserverInput;

// Logical
class ObserverLogic;
class ProjectileLogic;
class TestLogic;

// Visual
class ObserverCamera;
class PlanetarySurface;

class SolidBlackComponentModule :
            public ComponentModule {
public:
    void registerComponents(ComponentFactory* factory);
};
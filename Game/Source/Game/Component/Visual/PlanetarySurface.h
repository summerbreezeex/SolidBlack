#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/VisualComponent.h"
#include "Engine/Noise/Noise.h"

#include "Game/Component/Visual/PlanetarySurface/TerrainQuadtree.h"

class PlanetarySurface :
            public VisualComponent {
public:
    PlanetarySurface(ComponentFactory* factory);

    void enterScene(Scene* scene);
    void leaveScene();

    void logicUpdate(Ogre::Real timeStep);

    int getDiameter() const;
    int getRadius() const;

    int getTessellation() const;

    const NoiseFunction* getNoiseFunction() const;

private:
    void initializeNoise();

    ComponentAttribute<int> diameter;
    ComponentAttribute<std::string> noiseFunctionName;

    Ogre::Camera* sceneCamera;

    int tessellation;
    NoiseFunctionPtr noiseFunction;
    std::vector<TerrainQuadtreePtr> terrainPatchTrees;
};
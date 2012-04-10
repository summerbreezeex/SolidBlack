#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Threading/Task.h"

#include "Game/Component/Visual/PlanetarySurface/TerrainPatchData.h"

class PlanetarySurface;

class TerrainQuadtree;
typedef std::shared_ptr<TerrainQuadtree> TerrainQuadtreePtr;

class TerrainQuadtree {
public:
    TerrainQuadtree(PlanetarySurface* planetarySurface, Ogre::SceneNode* sceneNode, int size, TerrainQuadtree* parent = nullptr);
    ~TerrainQuadtree();

    void update(Ogre::Camera* camera);

    void split();
    void join();

    PlanetarySurface* getPlanetarySurface();

    Ogre::SceneNode* getSceneNode();
    Ogre::SceneNode* getRootSceneNode();

    int getSize() const;

    bool isLoaded() const;

private:
    void buildMesh();

    PlanetarySurface* planetarySurface;

    Ogre::SceneNode* sceneNode;

    int size;

    Ogre::ManualObject* terrainPatch;

    bool splitFlag;
    bool loadedFlag;
    bool meshBuiltFlag;

    TerrainQuadtree* parent;
    std::vector<TerrainQuadtreePtr> children;

    Task<TerrainPatchDataPtr> dataTask;
};
#pragma once

#include <OgrePrerequisites.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "Engine/StlCommon.h"

class TerrainQuadtree;

class TerrainPatchData {
public:
    TerrainPatchData(TerrainQuadtree* tree);

    void buildMesh(Ogre::ManualObject* mesh);

    Ogre::Vector3 getVertex(int x, int z);
    Ogre::Vector3 getVertexNormal(int x, int z);
    Ogre::Vector3 getNormal(int x, int z);

private:
    const Ogre::Vector3 mapToSphere(Ogre::Vector3 position, Ogre::Real radius);

    TerrainQuadtree* tree;

    int tessellation;

    std::vector<std::vector<Ogre::Vector3>> vertices;
    std::vector<std::vector<Ogre::Vector3>> normals;
    std::vector<std::vector<Ogre::Real>> heights;

    std::vector<Ogre::Vector3> processedPositions;
    std::vector<Ogre::Vector3> processedNormals;
    std::vector<Ogre::Vector3> processedTextureCoords;

    std::vector<int> processedIndices;

};

typedef std::shared_ptr<TerrainPatchData> TerrainPatchDataPtr;
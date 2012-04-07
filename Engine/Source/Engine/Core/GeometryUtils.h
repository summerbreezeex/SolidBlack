#pragma once

#include "Engine/StlCommon.h"

class GeometryUtils {
public:
    static void createSphere(Ogre::VertexData*& vertexData, Ogre::IndexData*& indexData, Ogre::Real radius, int numRings, int numSegments, bool normals, bool texCoords);
    static void createCone(Ogre::VertexData*& vertexData, Ogre::IndexData*& indexData, Ogre::Real radius, Ogre::Real height, int numVerticesInBase);

    static void createQuad(Ogre::VertexData*& vertexData);
};

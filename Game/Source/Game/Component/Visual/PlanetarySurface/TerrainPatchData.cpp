#include <OgreManualObject.h>
#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "Game/Component/Visual/PlanetarySurface.h"
#include "Game/Component/Visual/PlanetarySurface/TerrainQuadtree.h"

#include "TerrainPatchData.h"

TerrainPatchData::TerrainPatchData(TerrainQuadtree* tree) :
        tree(tree),
        tessellation(tree->getPlanetarySurface()->getTessellation()),
        vertices(tessellation + 3, std::vector<Ogre::Vector3>(tessellation + 3)),
        normals(tessellation + 3, std::vector<Ogre::Vector3>(tessellation + 3)),
        heights(tessellation + 3, std::vector<Ogre::Real>(tessellation + 3, 0.0)) {
    int patchSize = tree->getSize();
    Ogre::Real halfPatchSize = Ogre::Real(patchSize / 2);
    Ogre::Real delta = (Ogre::Real)patchSize * (1.0 / (Ogre::Real)tessellation);

    Ogre::SceneNode* patchSceneNode = tree->getSceneNode();
    Ogre::SceneNode* planetarySceneNode = tree->getPlanetarySurface()->getSceneNode();

    Ogre::Real planetaryRadius = (Ogre::Real)tree->getPlanetarySurface()->getRadius();

    for (int z = -1; z < tessellation + 2; ++z) {
        for (int x = -1; x < tessellation + 2; ++x) {
            Ogre::Vector3 position(-halfPatchSize + delta * x, 0.0, -halfPatchSize + delta * z);
            Ogre::Vector3 planetaryPosition = planetarySceneNode->convertWorldToLocalPosition(patchSceneNode->convertLocalToWorldPosition(position));
            planetaryPosition = mapToSphere(planetaryPosition, planetaryRadius);
            Ogre::Vector3 normal = planetaryPosition.normalisedCopy();
            Ogre::Real height = tree->getPlanetarySurface()->getNoiseFunction()->getValue(planetaryPosition);

            planetaryPosition = planetarySceneNode->convertLocalToWorldPosition(planetaryPosition);
            position = patchSceneNode->convertWorldToLocalPosition(planetaryPosition);

            normal = (tree->getRootSceneNode()->getOrientation().Inverse() * normal).normalisedCopy();

            vertices[z + 1][x + 1] = position;
            normals[z + 1][x + 1] = normal;
            heights[z + 1][x + 1] = height;
        }
    }

    for (int z = 0; z < tessellation + 1; ++z) {
        for (int x = 0; x < tessellation + 1; ++x) {
            processedPositions.push_back(getVertex(x, z));
            processedNormals.push_back(getVertexNormal(x, z));
            processedTextureCoords.push_back(getNormal(x, z));
        }
    }

    // Add triangles.
    for (int z = 0; z < tessellation; ++z) {
        int zOffset = z * (tessellation + 1);
        for (int x = 0; x < tessellation; ++x) {
            int indices[4] = {
                zOffset + x,
                zOffset + x + 1,
                zOffset + tessellation + 1 + x,
                zOffset + tessellation + 1 + x + 1
            };

            processedIndices.push_back(indices[0]);
            processedIndices.push_back(indices[2]);
            processedIndices.push_back(indices[1]);
            processedIndices.push_back(indices[2]);
            processedIndices.push_back(indices[3]);
            processedIndices.push_back(indices[1]);
        }
    }
}

void TerrainPatchData::buildMesh(Ogre::ManualObject* mesh) {
    int vertexCount = processedPositions.size();
    for (int i = 0; i < vertexCount; ++i) {
        mesh->position(processedPositions[i]);
        mesh->normal(processedNormals[i]);
        mesh->textureCoord(processedTextureCoords[i]);
    }

    int indexCount = processedIndices.size();
    for (int i = 0; i < indexCount; ++i) {
        mesh->index(processedIndices[i]);
    }
}

Ogre::Vector3 TerrainPatchData::getVertex(int x, int z) {
    x += 1;
    z += 1;
    return vertices[z][x] + heights[z][x] * normals[z][x];
}

Ogre::Vector3 TerrainPatchData::getVertexNormal(int x, int z) {
    Ogre::Vector3 v = getVertex(x, z);

    Ogre::Vector3 vs[4] = {
        getVertex(x + 1, z),
        getVertex(x - 1, z),
        getVertex(x, z + 1),
        getVertex(x, z - 1)
    };

    Ogre::Vector3 ws[2] = {
        getVertex(x + 1, z - 1),
        getVertex(x - 1, z + 1)
    };

    Ogre::Vector3 ns[6] = {
        (vs[2] - v).crossProduct(vs[0] - v).normalisedCopy(),
        (vs[3] - v).crossProduct(vs[1] - v).normalisedCopy(),

        (vs[1] - v).crossProduct(ws[1] - v).normalisedCopy(),
        (ws[1] - v).crossProduct(vs[2] - v).normalisedCopy(),

        (vs[0] - v).crossProduct(ws[0] - v).normalisedCopy(),
        (ws[0] - v).crossProduct(vs[3] - v).normalisedCopy(),
    };

    return ((ns[0] + ns[1] + ns[2] + ns[3] + ns[4] + ns[5]) / 6.0).normalisedCopy();
}

Ogre::Vector3 TerrainPatchData::getNormal(int x, int z) {
    x += 1;
    z += 1;
    return (normals[z][x]).normalisedCopy();
}

const Ogre::Vector3 TerrainPatchData::mapToSphere(Ogre::Vector3 position, Ogre::Real radius) {
    position /= radius;

    Ogre::Vector3 w(position);
    position.x *= Ogre::Math::Sqrt(1.0 - (w.y * w.y) / 2.0 - (w.z * w.z) / 2.0 + (w.y * w.y * w.z * w.z) / 3.0);
    position.y *= Ogre::Math::Sqrt(1.0 - (w.z * w.z) / 2.0 - (w.x * w.x) / 2.0 + (w.z * w.z * w.x * w.x) / 3.0);
    position.z *= Ogre::Math::Sqrt(1.0 - (w.x * w.x) / 2.0 - (w.y * w.y) / 2.0 + (w.x * w.x * w.y * w.y) / 3.0);
    position *= radius;

    return position;
}
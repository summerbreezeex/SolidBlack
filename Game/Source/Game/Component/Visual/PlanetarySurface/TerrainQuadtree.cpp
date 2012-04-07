#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreManualObject.h>
#include <OgreMesh.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Spacial/Transform.h"
#include "Engine/Core/Engine.h"

#include "Game/Component/Visual/PlanetarySurface.h"
#include "Game/Component/Visual/PlanetarySurface/TerrainPatchData.h"

#include "TerrainQuadtree.h"

TerrainQuadtree::TerrainQuadtree(PlanetarySurface* planetarySurface, Ogre::SceneNode* sceneNode, int size, TerrainQuadtree* parent) :
        planetarySurface(planetarySurface),
        sceneNode(sceneNode),
        size(size),
        terrainPatch(nullptr),
        splitFlag(false),
        loadedFlag(false),
        meshBuiltFlag(false),
        parent(parent) {
    Engine* engine = planetarySurface->getScene()->getEngine();

    dataTask = engine->getTaskPool()->schedule<TerrainPatchDataPtr>([&] {
        return TerrainPatchDataPtr(new TerrainPatchData(this));
    });
}

TerrainQuadtree::~TerrainQuadtree() {
    children.clear();

    if (sceneNode) {
        sceneNode->removeAndDestroyAllChildren();
    }

    if (!meshBuiltFlag) {
        dataTask.getResult();
    } else {
        planetarySurface->getScene()->getSceneManager()->destroyManualObject(terrainPatch);
        terrainPatch = nullptr;
    }
}

void TerrainQuadtree::update(Ogre::Camera* camera) {
    if (!meshBuiltFlag && dataTask.isDone()) {
        buildMesh();
    }

    auto boundingBox = sceneNode->_getWorldAABB();
    if (boundingBox.isNull() || !meshBuiltFlag) {
        return;
    }

    if (splitFlag) {
        foreach (child, children) {
            (*child)->update(camera);
        }
    }

    if (splitFlag && terrainPatch->isVisible()) {
        bool hide = true;

        foreach (child, children) {
            if (!(*child)->isLoaded()) {
                hide = false;
            }
        }

        if (hide) {
            terrainPatch->setVisible(false);

            foreach (child, children) {
                (*child)->terrainPatch->setVisible(true);
            }
        }
    }

    Ogre::Vector3 worldPosition = boundingBox.getCenter();

    Ogre::Real distance = camera->getRealPosition().distance(worldPosition);

    if (size > planetarySurface->getTessellation() && !splitFlag && distance < Ogre::Real(size) * 0.8) {
        split();
    } else if (splitFlag && distance > Ogre::Real(size) * 0.88) {
        join();
    }
}

void TerrainQuadtree::split() {
    splitFlag = true;

    int halfSize = size / 2;
    Ogre::Real quarterSize = Ogre::Real(size / 4);

    Ogre::SceneNode* childNodes[4] = {
        sceneNode->createChildSceneNode(Ogre::Vector3(-quarterSize, 0.0, -quarterSize)),
        sceneNode->createChildSceneNode(Ogre::Vector3(quarterSize, 0.0, -quarterSize)),
        sceneNode->createChildSceneNode(Ogre::Vector3(quarterSize, 0.0, quarterSize)),
        sceneNode->createChildSceneNode(Ogre::Vector3(-quarterSize, 0.0, quarterSize))
    };

    for (int i = 0; i < 4; ++i) {
        children.push_back(std::make_shared<TerrainQuadtree>(planetarySurface, childNodes[i], halfSize, this));
    }
}

void TerrainQuadtree::join() {
    splitFlag = false;
    terrainPatch->setVisible(true);
    sceneNode->removeAllChildren();
    children.clear();
}

PlanetarySurface* TerrainQuadtree::getPlanetarySurface() {
    return planetarySurface;
}

Ogre::SceneNode* TerrainQuadtree::getSceneNode() {
    return sceneNode;
}

Ogre::SceneNode* TerrainQuadtree::getRootSceneNode() {
    if (parent) {
        return parent->getRootSceneNode();
    } else {
        return sceneNode;
    }
}

int TerrainQuadtree::getSize() const {
    return size;
}

bool TerrainQuadtree::isLoaded() const {
    return loadedFlag;
}

void TerrainQuadtree::buildMesh() {
    assert(!terrainPatch);
    assert(!meshBuiltFlag);

    auto data = dataTask.getResult();
    dataTask = Task<TerrainPatchDataPtr>();
    loadedFlag = true;

    const int tessellation = getPlanetarySurface()->getTessellation();

    terrainPatch = getPlanetarySurface()->getScene()->getSceneManager()->createManualObject();
    terrainPatch->setDynamic(false);
    terrainPatch->estimateVertexCount((tessellation + 1) * (tessellation + 1));
    terrainPatch->estimateIndexCount(tessellation * tessellation * 6);
    if (parent) {
        terrainPatch->setVisible(false);
    }
    terrainPatch->begin("Terrain");

    data->buildMesh(terrainPatch);

    meshBuiltFlag = true;
    terrainPatch->end();
    sceneNode->attachObject(terrainPatch);
}